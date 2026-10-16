# Half-Life-Repo
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


And finally done!
