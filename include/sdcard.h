/*
*
* AUTHOR: dreamer1234
* Bus control code from: https://github.com/Jason2866/WiFi-SDCard
*
*/


#include <SimpleFTPServer.h>
#include <SPI.h>
#include <SD.h>
#include <sdios.h>
#include <SdFat.h>


// SD card chip select pin
const int CHIP_SELECT_PIN = 4;               // Default SS pin for SPI
#define SD_CS		4
#define MISO		5
#define MOSI		6
#define SCLK		7

#define SPI_BLOCKOUT_PERIOD	20000UL 

//void takeBusControl();
//void relinquishBusControl();
void InitializeSDCard();
void UnmountSDCard();
