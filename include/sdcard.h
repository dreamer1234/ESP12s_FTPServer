/*
*
* AUTHOR: dreamer1234
* Bus control code from: https://github.com/Jason2866/WiFi-SDCard
*
*/


#include <SimpleFTPServer.h>
#include <SPI.h>
#include <SD.h>
//#include <sdios.h>

#ifdef ESP8266
    #define SD_CS		4
    #define MISO		12
    #define MOSI		13
    #define SCLK		14
    #define CS_SENSE	5
#endif

#ifdef ESP32
    #define SD_CS		4
    #define MISO		5
    #define MOSI		6
    #define SCLK		7
#endif


#define SPI_BLOCKOUT_PERIOD	20000UL 
/*
void takeBusControl();
void relinquishBusControl();
*/
void InitializeSDCard();
void UnmountSDCard();
