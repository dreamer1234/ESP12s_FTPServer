/*
*
*  AUTHOR: dreamer1234
*  Parse Wifi credentials code from: https://github.com/Jason2866/WiFi-SDCard
*
*/

#include <wifi.h>
#include <ESP8266mDNS.h>
#include <sdcard.h>

#define HOSTNAME    "ESP8266"

void ConnectToWifi(){

  // WiFi credentials by default
  const char* WIFI_SSID = "BTT_TF_CLOUD";    		// Replace with your WiFi SSID
  const char* WIFI_PASSWORD = "deib2wke9nn54n";    // Replace with your WiFi password

  // Get WiFi credentials from credentials.txt file 

  /* UNCOMMENT THE FOLLOWING LINES IF YOU WANT CREDENTIALS FROM TXT FILE
  * THE LINES ARE COMMENTED OUT BECAUSE MOUNTING THE SD CARD MAKES THE BOOT PROCESS 
  * A LOT SLOWER
  */

  /*********************************************************************
  while (!SD.begin(CS_SENSE)) {
    delay(500);
  }
   File file = SD.open("/credentials.txt", FILE_READ);
   int i=0;
   String ssid, passwd;
   while(file.available())
    {
      if(i == 0)
       ssid = file.readStringUntil('\n');
      else
       passwd = file.readStringUntil('\n');
       i++;
    }
    file.close();
   // Remove special characters Windows inserts in text files
   ssid.trim();
   passwd.trim();
  ************************************************************/

   // Connect to WiFi network
   WiFi.mode(WIFI_STA);
   WiFi.setPhyMode(WIFI_PHY_MODE_11N);
   WiFi.hostname(HOSTNAME);

   ////////// UNCOMMENT THE FOLLOWING LINE IF YOU WANT CREDENTIALS FROM TXT FILE
   /// WiFi.begin(ssid.c_str(), passwd.c_str());

   /// COMMENT THE FOLLOWING LINE IF YOU WANT CREDENTIALS FROM TXT FILE
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   
   
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }
   MDNS.begin(HOSTNAME);
   UnmountSDCard();
}