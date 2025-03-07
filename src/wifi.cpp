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

  UnmountSDCard();
  // WiFi credentials by default
  const char* WIFI_SSID = "BTT_TF_CLOUD";    		// Replace with your WiFi SSID
  const char* WIFI_PASSWORD = "deib2wke9nn54n";    // Replace with your WiFi password

   // Connect to WiFi network
   WiFi.mode(WIFI_STA);
   WiFi.setPhyMode(WIFI_PHY_MODE_11N);
   WiFi.hostname(HOSTNAME);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   
   
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }
   MDNS.begin(HOSTNAME);
   
}