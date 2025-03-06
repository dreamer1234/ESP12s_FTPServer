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


#define SD_CS		4
#define MISO		12
#define MOSI		13
#define SCLK		14
#define CS_SENSE	5


#define SPI_BLOCKOUT_PERIOD	20000UL 

void takeBusControl();
void relinquishBusControl();
void InitializeSDCard();
void UnmountSDCard();
