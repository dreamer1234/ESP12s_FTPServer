/*
*
*  AUTHOR: dreamer1234
*  Parse Wifi credentials code from: https://github.com/Jason2866/WiFi-SDCard
*
*/

#include <wifi_esp.h>
#include <sdcard.h>


#ifdef ESP8266
#include <ESP8266mDNS.h>
#define HOSTNAME    "ESP8266"
#endif

#ifdef ESP32
#include <ESPmDNS.h>
#define HOSTNAME    "ESP32"
#endif




void ConnectToWifi(){

  UnmountSDCard();
  // WiFi credentials by default
  const char* WIFI_SSID = "BTT_TF_CLOUD";    		// Replace with your WiFi SSID
  const char* WIFI_PASSWORD = "deib2wke9nn54n";    // Replace with your WiFi password

   // Connect to WiFi network
   WiFi.mode(WIFI_STA);
   #ifdef ESP8266
      WiFi.setPhyMode(WIFI_PHY_MODE_11N);
   #endif
   WiFi.hostname(HOSTNAME);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   
   
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }
   if (!MDNS.begin(HOSTNAME)) {
    while (1) {
      delay(1000);
    }
   }
   
}