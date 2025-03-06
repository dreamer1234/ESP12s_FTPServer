#include <sdcard.h>

/*
* AUTHOR: dreamer1234
*
* Bus control code from:
* https://github.com/Jason2866/WiFi-SDCard
* 
*/


 // LED is connected to GPIO2 on this board
#define INIT_LED			{pinMode(2, OUTPUT);}
#define LED_ON				{digitalWrite(2, LOW);}
#define LED_OFF				{digitalWrite(2, HIGH);}


bool weHaveBus = false;
volatile long spiBlockoutTime = 0;


 void takeBusControl()	{
  // ------------------------
    weHaveBus = true;
    LED_ON;
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
    LED_OFF;
    weHaveBus = false;
  }

void InitializeSDCard(){

   takeBusControl();
   // Wait for a short delay before initializing SD card
   delay(1000);
   // Initialize SD card
   
  // If other chips are connected to SPI bus, set to high the pin connected
  // to their CS before initializing Flash memory
   pinMode( CS_SENSE, OUTPUT );
   digitalWrite( CS_SENSE, HIGH );
   while (!SD.begin(CS_SENSE)) {
     delay(500);
   }
   pinMode( CS_SENSE, OUTPUT );
   digitalWrite( CS_SENSE, HIGH );
}

void UnmountSDCard(){
    // Unmounting SD card
    Serial.print("Unmounting SD card...");
    delay(1000);
    SD.end();
    relinquishBusControl();
    pinMode( CS_SENSE, INPUT );
    digitalWrite( CS_SENSE, HIGH );
}