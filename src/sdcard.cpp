#include <sdcard.h>

/*
* AUTHOR: dreamer1234
*
* Bus control code from:
* https://github.com/Jason2866/WiFi-SDCard
* 
*/


bool weHaveBus = false;
volatile long spiBlockoutTime = 0;

// Object for File system
SdFat sd;

/*

 void takeBusControl()	{
  // ------------------------
    weHaveBus = true;
    pinMode(MISO, SPECIAL);	
    pinMode(MOSI, SPECIAL);	
    pinMode(SCLK, SPECIAL);	
    pinMode(SD_CS, OUTPUT);
  }

// ------------------------
void relinquishBusControl()	{
  // ------------------------
    pinMode(MISO, INPUT);	
    pinMode(MOSI, INPUT);	
    pinMode(SCLK, INPUT);	
    pinMode(SD_CS, INPUT);
    weHaveBus = false;
  }
*/
void InitializeSDCard(){

  // takeBusControl();
   // Wait for a short delay before initializing SD card
   delay(1000);
   // Initialize SD card
   SPI.begin(SCLK,MISO,MOSI,SD_CS);
  // If other chips are connected to SPI bus, set to high the pin connected
  // to their CS before initializing Flash memory
   pinMode( SD_CS, OUTPUT );
   digitalWrite( SD_CS, HIGH );
  /*
   while (!SD.begin(SD_CS)) {
     delay(500);
   } */
   
  if( ! sd.begin( SD_CS, SD_SCK_MHZ( 50 )))
  {
	Serial.println("unable to mount SD card");
    while( true ) ;
  } 
}

void UnmountSDCard(){
    // Unmounting SD card
    Serial.print("Unmounting SD card...");
    delay(1000);
//    SD.end();
//    relinquishBusControl();
    sd.end();
    /*pinMode(MISO, INPUT);	
    pinMode(MOSI, INPUT);	
    pinMode(SCLK, INPUT);	
    pinMode(SD_CS, INPUT);
    digitalWrite( SD_CS, HIGH );*/
}