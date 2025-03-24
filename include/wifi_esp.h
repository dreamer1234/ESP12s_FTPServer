/*
*
*  AUTHOR: dreamer1234
*
*/


#include <SimpleFTPServer.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#ifdef ESP32
#include <WiFi.h>
#endif

#define WIFI_SSID_LEN 32
#define WIFI_PASSWD_LEN 64

void ConnectToWifi();
