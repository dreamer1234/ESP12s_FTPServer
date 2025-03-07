/*
 * Simple FTP Server based in the code of the following repo:

 https://github.com/xreef/SimpleFTPServer

 *
 * AUTHOR: Renzo Mischianti
 * URL: https://www.mischianti.org
 *
 * DESCRIPTION:
 * This example demonstrates how to use the SimpleFTPServer library
 * with an ESP32 and an SD card module. The ESP32 connects to a WiFi network
 * and initializes an FTP server for file transfers.
 *
 * FEATURES:
 * - WiFi connection to local network
 * - SD card initialization for file storage
 * - FTP server setup for file uploads and downloads
 *
 * *************************
 * AUTHOR: dreamer1234
 * 
 * - Added DNS support,so you don't need the IP Address to connect to the FTP Server
 * 
 */

 #include <SimpleFTPServer.h>
 #include <wifi.h>
 #include <ESP8266mDNS.h>

 
 // FTP server instance
 FtpServer ftpServer;
 
 void setup() {
 
   // Connect to WiFi
   ConnectToWifi(); 
   // Start FTP server with username and password
  ftpServer.begin("user", "password"); // Replace with your desired FTP credentials
  Serial.println("FTP server started!");
  
 }
 
 void loop() {
   
  MDNS.update();
  // Handle FTP server operations
  ftpServer.handleFTP(); // Continuously process FTP requests
 }
