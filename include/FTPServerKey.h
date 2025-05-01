/*
 * FtpServer Arduino, esp8266 and esp32 library for Ftp Server
 * Derived form Jean-Michel Gallego version
 *
 * AUTHOR:  Renzo Mischianti
 *
 * https://www.mischianti.org/2020/02/08/ftp-server-on-esp8266-and-esp32
 *
 */

/*******************************************************************************
 **                                                                            **
 **                         SETTINGS FOR FTP SERVER                            **
 **                                                                            **
 *******************************************************************************/

#ifndef FTP_SERVER_CONFIG_H
#define FTP_SERVER_CONFIG_H

#define STORAGE_SDFAT1 		1 	// Library SdFat version 1.4.x
#define STORAGE_SDFAT2 		2 	// Library SdFat version >= 2.0.2
#define STORAGE_SD 			5 	// Standard SD library (suitable for Arduino esp8266 and esp32

#define NETWORK_ESP8266 		(2) 	// Standard ESP8266WiFi
#define NETWORK_ESP32 			(6) 	// Standard WiFi library


// esp8266 configuration
#ifndef DEFAULT_FTP_SERVER_NETWORK_TYPE_ESP8266
	#define DEFAULT_FTP_SERVER_NETWORK_TYPE_ESP8266 	NETWORK_ESP8266
	#define DEFAULT_STORAGE_TYPE_ESP8266 				STORAGE_SD
#endif
// esp32 configuration
#ifndef DEFAULT_FTP_SERVER_NETWORK_TYPE_ESP32
	#define DEFAULT_FTP_SERVER_NETWORK_TYPE_ESP32 		NETWORK_ESP32
	#define DEFAULT_STORAGE_TYPE_ESP32 					STORAGE_SDFAT2
#endif

#define UTF8_SUPPORT

#define SD_CS_PIN 4
// Disconnect client after 5 minutes of inactivity (expressed in seconds)
#ifndef FTP_TIME_OUT
	#define FTP_TIME_OUT  5 * 60
#endif


// Wait for authentication for 10 seconds (expressed in seconds)
#ifndef FTP_AUTH_TIME_OUT
	#define FTP_AUTH_TIME_OUT 10
#endif


// Size of file buffer for read/write
// Transfer speed depends of this value
// Best value depends on many factors: SD card, client side OS, ... 
// But it can be reduced to 512 if memory usage is critical.
#ifndef FTP_BUF_SIZE && defined(ESP8266)
	#define FTP_BUF_SIZE 1024 //2048 //1024 // 512
#endif
#ifndef FTP_BUF_SIZE && defined(ESP32)
	#define FTP_BUF_SIZE 2048 //2048 //1024 // 512
#endif

#endif // FTP_SERVER_CONFIG_H
