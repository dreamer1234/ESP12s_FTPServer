# ESP12s_FTPServer
FTP Server over with SD card support using FAT filesystem. 
- FTP Server code mainly based in the code by Renzo Mischianti: https://github.com/xreef/SimpleFTPServer
- Bus control code from: https://github.com/Jason2866/WiFi-SDCard
- Lots of other sources like forums and personal code.

# Description
The idea behind this project is to have a little board (ESP12s) that connects to WiFi and acts as and FTP Server, at the same time that is sharing the SD card slot with other board that is using it. 

In this case, the code has been developed and tested with the board BTT-SD-TF-Cloud-V1.0: https://github.com/bigtreetech/BTT-SD-TF-Cloud-V1.0

Things:
  - The board is attached using the SD pins to a main board
  - The main board that works and is used in this setup is the Olimex ESP32-SBC-FABGL: https://github.com/OLIMEX/ESP32-SBC-FabGL

Image with the setup:

![imagen](https://github.com/user-attachments/assets/7f207acc-6d92-4e11-ba2f-1cb0e08e6613)


# Features
- The main ESP32 board can use the SD slot all the time but when an FTP transfer is in course by the SLAVE ESP12s board (when it takes the ownership of the SD card)
- After the FTP transfer is finished, the SLAVE ESP12s board releases the bus, so the main ESP32 board can use it.
- DNS name added so a connection can be stablished without knowing the IP Address when the client is connecting using the same network. Name to connect by default: ESP8266

# Installation
- Just clone the repository and use Platformio to build and upload the code to the ESP12s board. To upload the code to the board, just remember you need to first press the BOOT button, then connect the USB cable to the board and the computer and then release the BOOT button.

# Client configuration
- Just read the guide inside the "doc" folder of the repository

# Notes
- The development is in very early stage, and I'm not sure how is going to evolve or when or if it's going to be mantained.
- The code is distributed AS-IS. I'm not responsible for any issue.
- User and password by default: user / password . Change them in the code before compiling if you want different ones.

# TO-DO
- Clean up code.
- Pending to add the reading of Wireless credentials from TXT file on the SD Card.
- Try to make it work with the LilyGo FabGL TTGO VGA32 as main board. The LilyGo FabGL TTGO VGA32, does not even power on when the ESP12s board is connected to the SD card slot. I don't know it it can be solved or how. Olimex board seems to work pretty nice, though.
- Additional features using the WiFi connection (perhaps).
