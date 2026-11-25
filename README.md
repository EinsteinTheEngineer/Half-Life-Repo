 # Half-Life-Repo

# WEEK 1

PURPOSE:
The purpose of my project is to create a simple yet extremely useful Flight computer, that can also be used for rockets, and this would simply send data, of temperature, bearing, and height, I can also create a velocity time graph with velocity put on the graph, and then simple derivate that to get acceleration, or I can just use the accelerometer, the MPU, and use that to give me a A vs. T graph. Why it exists: The reason is that flight computer is expensive and this is a fully done PCB, instead of me having to use a breadboard and have to worry about a loose connection, I can asssure myself that the copper traces will work. I love building plane and rockets, but what I like more is seeing them work and not fail, for this I need data! So I created this board to collect me data and so if it does fail, why and how can I prevent it the next time.





My project is a flight computer that will have multiple sensors talk to and esp32 wroom chip that will write the data to an SD card that will store it. The board consists of the following: ESP32-WROOM chip, MPU6050, BMP280, and an SD card logger. This was my plan at first, and it was changed a lot though. I add a DC to DC Buck converter it would convert 6v dc to 3.3v dc for the esp to then spit out 3.3v logic.
Started as this:
<img width="1512" height="1200" alt="Screenshot 2026-10-05 224937" src="https://github.com/user-attachments/assets/00e4758d-59ce-4b09-8c4a-6a31906f12e1" />

Then added the extra components:
<img width="1586" height="1428" alt="Screenshot 2026-10-06 222736" src="https://github.com/user-attachments/assets/5b6a43c8-67ef-415d-bc12-23b9d0270ce2" />

Wired ground and live:
<img width="2028" height="1462" alt="Screenshot 2026-10-06 225111" src="https://github.com/user-attachments/assets/c5521aea-25f7-435e-b667-f1d0dec20b07" />

Wired the MPU: 
<img width="734" height="872" alt="Screenshot 2026-10-07 222204" src="https://github.com/user-attachments/assets/76f4b9a8-c431-4b24-bc5d-8e2b5e652464" />

Wired the BMP:
<img width="286" height="194" alt="Screenshot 2026-10-07 223501" src="https://github.com/user-attachments/assets/4f6c2fda-7b6b-4cc0-8495-1a5792b8e8d0" />

Wired the SD card:
<img width="544" height="366" alt="Screenshot 2026-10-07 224235" src="https://github.com/user-attachments/assets/e10dfce4-8377-4dde-bd17-e0c92aceebe9" />

Finalized Schematic:
<img width="1232" height="942" alt="Screenshot 2026-10-10 120510" src="https://github.com/user-attachments/assets/85a80a59-e5ce-4a2e-bed0-7fd00e29d2dd" />

After fighting the ERC test
<img width="990" height="586" alt="Screenshot 2026-10-10 120623" src="https://github.com/user-attachments/assets/f3c56324-35c0-4427-9de7-4919a5a14e33" />

Then routed the board:
<img width="522" height="568" alt="Screenshot 2026-10-10 120944" src="https://github.com/user-attachments/assets/73e01116-fdee-4277-9529-5b1d563f19c8" />

The 3d View
<img width="1148" height="1022" alt="image" src="https://github.com/user-attachments/assets/e8037be4-17c5-4d21-a429-5a5c477eb6ba" />


And finally done!


Here is My BOM for the parts I am using:

Designator	Category	Part / Value	Qty	Package / Footprint	Est. Unit Price (USD)	Est. Line Total (USD)	Distributor Link
U1	IC / Module	Espressif ESP32-WROOM-32E (or 32U)	1	ESP32-WROOM-32	7.21	7.21	digikey.com
U2	Sensor	Bosch BMP280	1	LGA-8 (2.0x2.5mm)	3	3	digikey.com
U3	Sensor	TDK InvenSense MPU-6050	1	QFN-24 (4x4mm)	4.25	4.25	digikey.com
U4	Power IC	Diodes Inc. AP63203WU-7	1	TSOT-23-6	0.65	0.65	digikey.com
U5	Interface IC	WCH CH340C	1	SOP-16	0.9	0.9	lcsc.com
J1	Connector	MicroSD Card Slot (Push-Push)	1	MicroSD_Card_Det	1.1	1.1	digikey.com
J2	Connector	2-Pin JST-PH 2.0mm Header	1	JST_PH_B2B-PH-K	0.25	0.25	digikey.com
J3	Connector	HRO TYPE-C-31-M-12 (16-Pin USB-C)	1	USB_C_Receptacle_16P	0.55	0.55	lcsc.com
SW1	Switch	SPDT SMD Slide Switch	1	SW_SPDT_PCM12	0.4	0.4	digikey.com
Q1, Q2	Transistor	S8050 (or MMBT3904) NPN	2	SOT-23	0.1	0.2	digikey.com
D1, D2	Diode	B5819W Schottky Diode	2	SOD-123	0.15	0.3	digikey.com
R1, R2	Resistor	5.1 kΩ (1%)	2	0603 (1608 Metric)	0.1	0.2	digikey.com
R3, R4, R_EN, R_IO0, R_SD1–3	Resistor	10 kΩ (1%)	7	0603 (1608 Metric)	0.1	0.7	digikey.com
R_TX	Resistor	1 kΩ (1%)	1	0603 (1608 Metric)	0.1	0.1	digikey.com
R_SDA, R_SCL	Resistor	4.7 kΩ (1%)	2	0603 (1608 Metric)	0.1	0.2	digikey.com
C5	Capacitor	2.2 nF (50V X7R)	1	0603 (1608 Metric)	0.1	0.1	digikey.com
C1–C4, C_DEC1–5	Capacitor	100 nF (16V/25V X7R)	7	0603 (1608 Metric)	0.1	0.7	digikey.com
C_EN	Capacitor	1 µF (16V X7R)	1	0603 (1608 Metric)	0.1	0.1	digikey.com
C_IN, C_BULK1–2	Capacitor	10 µF (25V X5R/X7R)	3	0805 (2012 Metric)	0.15	0.45	digikey.com
C6	Capacitor	22 µF (16V X5R/X7R)	1	0805 (2012 Metric)	0.2	0.2	digikey.com
L1	Inductor	3.3 µH (≥1.5A Shielded)	1	1210 (3225 Metric)	0.45	0.45	digikey.com

# WEEK 2

The purpose of this project is the create an enclosure for my PCB that I designed in week 1, this will make sure it isn't just sitting in there just chilling, I made sure to add mounting holes, and vents to make sure it will sit there and that it will have some breathability, and so it can cool, with the use of a fan two, since it will also use its antenna to communicate with my computer that's on the ground. So that means I technically have two ways to get data, from the SD card and from communication with my computer. I would trust the SD card more since the computer may have lost packets on the way and it could not be as reliable as a SD card, but it there as another way to have data.

<img width="1150" height="742" alt="image" src="https://github.com/user-attachments/assets/899c754f-2885-415f-ad31-b0a64ea5dabe" />

Me personally, I printed this with PLA, since its cheap, light weight, and it's not like there's going to be such high temperatures, hence there is also a fan there for a reason.
PLA, print with 10-15% infill, you'll probably need support material, I have a K1C so no multi-material, so I just printed PLA supports.

# WEEK 3

This week I decided to create a recorder, it records sounds and stuff like that. The purpose for why I wanted to do this was because it was relatively simple, plus I learned about this new board the ESP32-S3-Zero, it's so good. It so useful, though its small it does a lot of things whilst being small. I was the perfect addition to the board, and just the same simple way of coding it. At first, I was about to use the actual esp32, which was most definitely going to be overkill for this simple guy. This board is a breakout board kind of, since it doesn't have an on-board ESP but the board will be put onto the thing.

Fully routed Schematic
<img width="248" height="694" alt="Screenshot 2026-10-25 212208" src="https://github.com/user-attachments/assets/0c8249b3-daeb-4f86-a8c7-041f82ada282" />


With the cut outs
<img width="414" height="716" alt="Screenshot 2026-10-25 212635" src="https://github.com/user-attachments/assets/f1133016-d9ac-4982-820e-f3c904f68a9c" />

3D view
<img width="396" height="876" alt="Screenshot 2026-10-25 212646" src="https://github.com/user-attachments/assets/b80edc1b-11a0-42ae-b9dd-951c3e18a122" />

Here's the BOM

"Reference","Qty","Value","DNP","Exclude from BOM","Exclude from Board","Footprint","Datasheet"
"C1","1","100","","","","Capacitor_SMD:C_0805_2012Metric","~"
"C2","1","10000","","","","Capacitor_SMD:C_0805_2012Metric","~"
"C3","1","C","","","","Capacitor_SMD:C_0805_2012Metric","~"
"D1","1","LED","","","","LED_THT:LED_D3.0mm","~"
"J1,J2","2","Conn_01x09_Pin","","","","Connector_PinSocket_2.54mm:PinSocket_1x09_P2.54mm_Vertical","~"
"J3","1","Conn_01x06_Pin","","","","Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical","~"
"J4","1","Micro_SD_Card","","","","Connector_Card:microSD_HC_Wuerth_693072010801","https://www.we-online.com/components/products/datasheet/693072010801.pdf"
"J5","1","Screw_Terminal_01x02","","","","TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal","~"
"R1","1","330","","","","Resistor_SMD:R_0805_2012Metric","~"
"SW1","1","SW_Push","","","","Button_Switch_THT:SW_PUSH_6mm","~"

# WEEK 4

This week I focused on a weather and display thing. This was a simple yet easy idea that I would like to keep on my desk. It will show date, time, weather, and just a sleek design. The purpose of this was to create something very useful, and it will be simple enough to be easy to do. 

<img width="1206" height="1312" alt="Screenshot 2026-11-01 211237" src="https://github.com/user-attachments/assets/6e33915b-e0bf-440c-a1ca-c1d28702c67c" />





