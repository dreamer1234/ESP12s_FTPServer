/*
*
*  AUTHOR: dreamer1234
*  Parse Wifi credentials code from: https://github.com/Jason2866/WiFi-SDCard
*
*/



#include <wifi.h>
#include <ESP8266mDNS.h>
#include <sdcard.h>
#include <stdio.h>
#include <string.h>


#define HOSTNAME    "ESP8266"

void ConnectToWifi(){
   // WiFi credentials
   const char* WIFI_SSID = "E380";    		// Replace with your WiFi SSID
   const char* WIFI_PASSWORD = "deib2wke9nn54n";    // Replace with your WiFi password
   // InitializeSDCard();
   // Get WiFi credentials from credentials.txt file . 
   /* File file = SD.open("/credentials.txt", FILE_READ);
   int i=0;
   String s,p;
   while(file.available())
    {
      if(i == 0)
       s = file.readStringUntil('\n');
      else
       p = file.readStringUntil('\n');
       i++;
    }
    file.close(); */
   // Connect to WiFi network
   Serial.println("Connecting to WiFi...");
   WiFi.mode(WIFI_STA);
   WiFi.setPhyMode(WIFI_PHY_MODE_11N);
   WiFi.hostname(HOSTNAME);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }
   MDNS.begin(HOSTNAME);
   UnmountSDCard();
}