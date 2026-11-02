
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_BMP085.h>
#include <time.h>

// =====================================
// WIFI SETTINGS
// =====================================

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Change these to your location
const float LATITUDE = 40.10;
const float LONGITUDE = -83.12;

// Cincinnati / Eastern time
const char* TIMEZONE = "EST5EDT,M3.2.0/2,M11.1.0/2";

// =====================================
// GPIO CONFIGURATION
// =====================================

// TFT Display
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8
#define TFT_BL   7

// BMP180
#define BMP_SDA 5
#define BMP_SCL 6

// =====================================
// OBJECTS
// =====================================

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);
Adafruit_BMP085 bmp;

// =====================================
// WEATHER VARIABLES
// =====================================

float outdoorTemp = 0;
float outdoorHumidity = 0;
float windSpeed = 0;
float pressureAPI = 0;

float localPressure = 0;
float localTemp = 0;

int currentWeatherCode = 0;

String forecastDates[7];
float forecastHigh[7];
float forecastLow[7];
int forecastCodes[7];

bool weatherAvailable = false;
bool bmpAvailable = false;

unsigned long lastWeatherUpdate = 0;

const unsigned long WEATHER_INTERVAL = 900000;

// =====================================
// WEATHER CODE CONVERSION
// =====================================

String weatherDescription(int code) {

  if (code == 0) return "Clear";
  if (code <= 2) return "Partly Cloudy";
  if (code == 3) return "Cloudy";
  if (code <= 48) return "Fog";
  if (code <= 57) return "Drizzle";
  if (code <= 67) return "Rain";
  if (code <= 77) return "Snow";
  if (code <= 82) return "Showers";
  if (code <= 86) return "Snow Showers";
  if (code <= 99) return "Thunderstorm";

  return "Unknown";
}

// =====================================
// WIFI CONNECTION
// =====================================

void connectWiFi() {

  Serial.println("Connecting to WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED &&
         attempts < 30) {

    delay(500);
    Serial.print(".");

    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("\nWiFi Connected!");
    Serial.println(WiFi.localIP());

  } else {

    Serial.println("\nWiFi connection failed.");
  }
}

// =====================================
// TIME SYNCHRONIZATION
// =====================================

void setupTime() {

  configTzTime(
    TIMEZONE,
    "pool.ntp.org",
    "time.nist.gov"
  );

  Serial.println("Synchronizing time...");
}

// =====================================
// GET WEATHER FROM OPEN-METEO
// =====================================

bool getWeather() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected.");
    return false;
  }

  String url =
    "https://api.open-meteo.com/v1/forecast?"
    "latitude=" + String(LATITUDE, 4) +
    "&longitude=" + String(LONGITUDE, 4) +
    "&current=temperature_2m,relative_humidity_2m,"
    "apparent_temperature,weather_code,pressure_msl,"
    "wind_speed_10m"
    "&daily=weather_code,temperature_2m_max,"
    "temperature_2m_min,precipitation_probability_max"
    "&forecast_days=7"
    "&timezone=auto";

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;

  Serial.println("Getting weather data...");

  if (!http.begin(client, url)) {
    return false;
  }

  int httpCode = http.GET();

  if (httpCode != HTTP_CODE_OK) {

    Serial.printf("HTTP error: %d\n", httpCode);

    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  DynamicJsonDocument doc(16000);

  DeserializationError error =
    deserializeJson(doc, payload);

  if (error) {

    Serial.println("JSON parsing failed.");
    return false;
  }

  JsonObject current = doc["current"];

  outdoorTemp = current["temperature_2m"];
  outdoorHumidity = current["relative_humidity_2m"];
  windSpeed = current["wind_speed_10m"];
  pressureAPI = current["pressure_msl"];

  currentWeatherCode = current["weather_code"];

  JsonObject daily = doc["daily"];

  JsonArray dates = daily["time"];
  JsonArray highs = daily["temperature_2m_max"];
  JsonArray lows = daily["temperature_2m_min"];
  JsonArray codes = daily["weather_code"];

  for (int i = 0; i < 7; i++) {

    forecastDates[i] = dates[i].as<String>();
    forecastHigh[i] = highs[i];
    forecastLow[i] = lows[i];
    forecastCodes[i] = codes[i];

  }

  weatherAvailable = true;

  Serial.println("Weather updated!");

  Serial.printf(
    "Outdoor temperature: %.1f C\n",
    outdoorTemp
  );

  return true;
}

// =====================================
// READ BMP180
// =====================================

void readBMP() {

  if (!bmpAvailable) return;

  localTemp = bmp.readTemperature();

  // Convert Pa to hPa
  localPressure = bmp.readPressure() / 100.0;

  Serial.printf(
    "Local pressure: %.2f hPa\n",
    localPressure
  );

  Serial.printf(
    "Local temperature: %.1f C\n",
    localTemp
  );
}

// =====================================
// DISPLAY TIME AND DATE
// =====================================

void drawTime() {

  struct tm timeInfo;

  if (!getLocalTime(&timeInfo)) {
    return;
  }

  char timeBuffer[20];
  char dateBuffer[30];

  strftime(
    timeBuffer,
    sizeof(timeBuffer),
    "%I:%M:%S %p",
    &timeInfo
  );

  strftime(
    dateBuffer,
    sizeof(dateBuffer),
    "%A, %b %d %Y",
    &timeInfo
  );

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  tft.setCursor(8, 8);
  tft.print(timeBuffer);

  tft.setTextSize(1);
  tft.setCursor(8, 32);
  tft.print(dateBuffer);
}

// =====================================
// DISPLAY CURRENT WEATHER
// =====================================

void drawCurrentWeather() {

  tft.drawRoundRect(
    5, 48, 310, 65, 6, ST77XX_CYAN
  );

  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(3);
  tft.setCursor(14, 57);

  if (weatherAvailable) {

    tft.print(outdoorTemp, 1);
    tft.print(" C");

  } else {

    tft.print("--.- C");
  }

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);

  tft.setCursor(175, 55);

  if (weatherAvailable) {
    tft.print(weatherDescription(currentWeatherCode));
  } else {
    tft.print("No weather data");
  }

  tft.setCursor(175, 73);

  if (weatherAvailable) {
    tft.print("Humidity: ");
    tft.print(outdoorHumidity, 0);
    tft.print("%");
  }

  tft.setCursor(175, 89);

  if (weatherAvailable) {
    tft.print("Wind: ");
    tft.print(windSpeed, 1);
    tft.print(" km/h");
  }
}

// =====================================
// DISPLAY BAROMETER
// =====================================

void drawPressure() {

  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(1);

  tft.setCursor(8, 119);
  tft.print("LOCAL BAROMETER (BMP180)");

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  tft.setCursor(8, 132);

  if (bmpAvailable) {

    tft.print(localPressure, 1);
    tft.print(" hPa");

  } else {

    tft.print("Sensor unavailable");
  }
}

// =====================================
// DISPLAY SEVEN DAY FORECAST
// =====================================

void drawForecast() {

  tft.setTextSize(1);
  tft.setTextColor(ST77XX_CYAN);

  tft.setCursor(8, 160);
  tft.print("7 DAY FORECAST");

  tft.drawLine(
    8, 173, 312, 173, ST77XX_WHITE
  );

  for (int i = 0; i < 7; i++) {

    int y = 179 + (i * 8);

    // Compact date
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(8, y);

    if (weatherAvailable) {

      tft.print(forecastDates[i].substring(5));

      tft.setCursor(85, y);
      tft.print(weatherDescription(forecastCodes[i]));

      tft.setCursor(250, y);
      tft.print(forecastHigh[i], 0);

      tft.print("/");
      tft.print(forecastLow[i], 0);

    } else {

      tft.print("Waiting for weather...");
      break;
    }
  }
}

// =====================================
// COMPLETE DISPLAY UPDATE
// =====================================

void updateDisplay() {

  tft.fillScreen(ST77XX_BLACK);

  drawTime();
  drawCurrentWeather();
  drawPressure();
  drawForecast();
}

// =====================================
// SETUP
// =====================================

void setup() {

  Serial.begin(115200);

  // Backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // SPI display
  SPI.begin(
    TFT_SCLK,
    -1,
    TFT_MOSI,
    TFT_CS
  );

  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  // I2C sensor
  Wire.begin(BMP_SDA, BMP_SCL);

  bmpAvailable = bmp.begin();

  if (bmpAvailable) {
    Serial.println("BMP180 detected!");
  } else {
    Serial.println("BMP180 not detected!");
  }

  connectWiFi();

  if (WiFi.status() == WL_CONNECTED) {

    setupTime();

    getWeather();
  }

  readBMP();

  updateDisplay();

  lastWeatherUpdate = millis();
}

// =====================================
// MAIN LOOP
// =====================================

void loop() {

  // Refresh weather every 15 minutes
  if (millis() - lastWeatherUpdate >=
      WEATHER_INTERVAL) {

    if (WiFi.status() != WL_CONNECTED) {
      connectWiFi();
    }

    if (WiFi.status() == WL_CONNECTED) {
      getWeather();
    }

    readBMP();

    updateDisplay();

    lastWeatherUpdate = millis();
  }

  // Update clock once per second
  static int previousSecond = -1;

  struct tm timeInfo;

  if (getLocalTime(&timeInfo, 10)) {

    if (timeInfo.tm_sec != previousSecond) {

      previousSecond = timeInfo.tm_sec;

      // Refresh screen clock without
      // requesting weather again.
      updateDisplay();
    }
  }

  delay(100);
}
