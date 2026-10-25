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

"Reference","Qty","Value","DNP","Exclude from BOM","Exclude from Board","Footprint","Datasheet"
"C1,C2,C3,C4","4","100","","","","Capacitor_SMD:C_0603_1608Metric","~"
"C5","1","2.2","","","","Capacitor_SMD:C_0603_1608Metric","~"
"J1","1","Micro_SD_Card_Det1","","","","microSD_HC_Hirose_DM3AT-SF-PEJM5","https://datasheet.lcsc.com/lcsc/2110151630_XKB-Connectivity-XKTF-015-N_C381082.pdf"
"J2","1","Screw_Terminal_01x02","","","","TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal","~"
"L1","1","6.8","","","","L_1210_3225Metric","~"
"SW1","1","SW_SPST","","","","SW_DIP_SPSTx01_Slide_6.7x4.1mm_W7.62mm_P2.54mm_LowProfile","~"
"U1","1","ESP32-WROOM-32E","","","","RF_Module:ESP32-WROOM-32D","https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf"
"U2","1","BMP280","","","","Package_LGA:Bosch_LGA-8_2x2.5mm_P0.65mm_ClockwisePinNumbering","https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMP280-DS001.pdf"
"U3","1","MPU-6050","","","","Sensor_Motion:InvenSense_QFN-24_4x4mm_P0.5mm","https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf"
"U4","1","AP63203WU","","","","Package_TO_SOT_SMD:TSOT-23-6","https://www.diodes.com/assets/Datasheets/AP63200-AP63201-AP63203-AP63205.pd

# WEEK 2

The purpose of this project is the create an enclosure for my PCB that I designed in week 1, this will make sure it isn't just sitting in there just chilling, I made sure to add mounting holes, and vents to make sure it will sit there and that it will have some breathability, and so it can cool, with the use of a fan two, since it will also use its antenna to communicate with my computer that's on the ground. So that means I technically have two ways to get data, from the SD card and from communication with my computer. I would trust the SD card more since the computer may have lost packets on the way and it could not be as reliable as a SD card, but it there as another way to have data.

<img width="1150" height="742" alt="image" src="https://github.com/user-attachments/assets/899c754f-2885-415f-ad31-b0a64ea5dabe" />
