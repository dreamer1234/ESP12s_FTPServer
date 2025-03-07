/*
 * FtpServer Arduino, esp8266 and esp32 library for Ftp Server
 * Derived form Jean-Michel Gallego version
 *
 * AUTHOR:  Renzo Mischianti
 *
 * https://www.mischianti.org/2020/02/08/ftp-server-on-esp8266-and-esp32
 * 
 * AUTHOR: dreamer1234
 *
 * Removed several lines since I'm only interested in the ESP8266 board
 */


/*******************************************************************************
 **                                                                            **
 **                       DEFINITIONS FOR FTP SERVER                           **
 **                                                                            **
 *******************************************************************************/

 #ifndef FTP_SERVER_H
 #define FTP_SERVER_H
 
 #include <FtpServerKey.h>

 
 #define FTP_SERVER_VERSION "2.1.10 (2025-01-11)"
 
 #if ARDUINO >= 100
 #include "Arduino.h"
 #else
 #include "WProgram.h"
 #endif

 #if !defined(FTP_SERVER_NETWORK_TYPE)
 // select Network type based
     #if defined(ESP8266)
         #if(NETWORK_ESP8266_242 == DEFAULT_FTP_SERVER_NETWORK_TYPE_ESP8266)
             #define ARDUINO_ESP8266_RELEASE_2_4_2
 
             #define FTP_SERVER_NETWORK_TYPE_SELECTED NETWORK_ESP8266_242
 
             #define FTP_SERVER_NETWORK_TYPE NETWORK_ESP8266
         #else
             #define FTP_SERVER_NETWORK_TYPE DEFAULT_FTP_SERVER_NETWORK_TYPE_ESP8266
         #endif
 
         #define STORAGE_TYPE DEFAULT_STORAGE_TYPE_ESP8266
     #elif defined(ESP32)
         #define FTP_SERVER_NETWORK_TYPE DEFAULT_FTP_SERVER_NETWORK_TYPE_ESP32
         #define STORAGE_TYPE DEFAULT_STORAGE_TYPE_ESP32
     #endif
 #endif
 
 #ifndef FTP_SERVER_NETWORK_TYPE_SELECTED
     #define FTP_SERVER_NETWORK_TYPE_SELECTED FTP_SERVER_NETWORK_TYPE
 #endif
 
 
 #if defined(ESP8266)
     #ifndef STORAGE_SD_FORCE_DISABLE
         #define STORAGE_SD_ENABLED
     #endif
     #ifndef STORAGE_SPIFFS_FORCE_DISABLE
         #define STORAGE_SPIFFS_ENABLED
     #endif
 #else
     #ifndef STORAGE_SD_FORCE_DISABLE
         #define STORAGE_SD_ENABLED
     #endif
 #endif
 
 
 // Includes and defined based on Network Type
 #if(FTP_SERVER_NETWORK_TYPE == NETWORK_ESP8266_ASYNC)
 
     // Note:
     //   No SSL/WSS support for client in Async mode
     //   TLS lib need a sync interface!
 
     #if defined(ESP8266)
         #include <ESP8266WiFi.h>
         //#include <WiFiClientSecure.h>
         #define FTP_CLIENT_NETWORK_CLASS WiFiClient
         //#define FTP_CLIENT_NETWORK_SSL_CLASS WiFiClientSecure
         #define FTP_SERVER_NETWORK_SERVER_CLASS WiFiServer

     #else
         #error "network type ESP8266 ASYNC only possible on the ESP mcu!"
     #endif
 
 #elif(FTP_SERVER_NETWORK_TYPE == NETWORK_ESP8266 || FTP_SERVER_NETWORK_TYPE == NETWORK_ESP8266_242)
 
         #if !defined(ESP8266)
             #error "network type ESP8266 only possible on the ESP mcu!"
         #endif
 
         #ifdef ESP8266
             #include <ESP8266WiFi.h>
         #else
             #include <ESP31BWiFi.h>
         #endif
         #define FTP_CLIENT_NETWORK_CLASS WiFiClient
         //#define FTP_CLIENT_NETWORK_SSL_CLASS WiFiClientSecure
         #define FTP_SERVER_NETWORK_SERVER_CLASS WiFiServer
         #define NET_CLASS WiFi
 //		#define CommandIs( a ) (command != NULL && ! strcmp_P( command, PSTR( a )))
 //		#define ParameterIs( a ) ( parameter != NULL && ! strcmp_P( parameter, PSTR( a )))

 #else
     #error "no network type selected!"
 #endif
 
 #if defined(ESP8266)
     #define CommandIs( a ) (command != NULL && ! strcmp_P( command, PSTR( a )))
     #define ParameterIs( a ) ( parameter != NULL && ! strcmp_P( parameter, PSTR( a )))
 #else
     #define CommandIs( a ) ( ! strcmp_PF( command, PSTR( a )))
     #define ParameterIs( a ) ( ! strcmp_PF( parameter, PSTR( a )))
 #endif
 
 #if(STORAGE_TYPE == STORAGE_SD)
     #include <SPI.h>
     #include <SD.h>
 
     #define STORAGE_MANAGER SD
       #define FTP_FILE File
       #define FTP_DIR File
 
     #define FTP_FILE_READ FILE_READ
     #define FTP_FILE_READ_ONLY FILE_READ
 #ifdef ESP32
     #define FTP_FILE_READ_WRITE FILE_WRITE
     #define FTP_FILE_WRITE_APPEND FILE_APPEND
 #else
     #define FTP_FILE_READ_WRITE FILE_WRITE
     #define FTP_FILE_WRITE_APPEND FILE_WRITE
 #endif
     #define FTP_FILE_WRITE_CREATE FILE_WRITE
 
     #define FILENAME_LENGTH 255
 #elif(STORAGE_TYPE == STORAGE_SD_MMC)
     #include <SPI.h>
     #include <SD_MMC.h>
 
     #define STORAGE_MANAGER SD_MMC
       #define FTP_FILE File
       #define FTP_DIR File
 
     #define FTP_FILE_READ FILE_READ
     #define FTP_FILE_READ_ONLY FILE_READ
     #define FTP_FILE_READ_WRITE FILE_WRITE
 #ifdef ESP32
     #define FTP_FILE_READ_WRITE FILE_WRITE
     #define FTP_FILE_WRITE_APPEND FILE_APPEND
 #else
     #define FTP_FILE_READ_WRITE FILE_WRITE
     #define FTP_FILE_WRITE_APPEND FILE_WRITE
 #endif
     #define FTP_FILE_WRITE_CREATE FILE_WRITE
 
     #define FILENAME_LENGTH 255
 
 #endif
 
 
 #define OPEN_CLOSE_SPIFFS
 #define OPEN_CLOSE_SD
 
 // Setup debug printing macros.
 #ifdef FTP_SERVER_DEBUG
     #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
     #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
 #else
     #define DEBUG_PRINT(...) {}
     #define DEBUG_PRINTLN(...) {}
 #endif
 
 #define FTP_CMD_PORT 21           // Command port on which server is listening
 #define FTP_DATA_PORT_DFLT 20     // Default data port in active mode
 #define FTP_DATA_PORT_PASV 50009  // Data port in passive mode
 
 #define FF_MAX_LFN 255            // max size of a long file name
 #define FTP_CMD_SIZE FF_MAX_LFN+8 // max size of a command
 #define FTP_CWD_SIZE FF_MAX_LFN+8 // max size of a directory name
 #define FTP_FIL_SIZE FF_MAX_LFN   // max size of a file name
 #define FTP_CRED_SIZE 16          // max size of username and password
 #define FTP_NULLIP() IPAddress(0,0,0,0)
 
 enum ftpCmd { FTP_Stop = 0,       //  In this stage, stop any connection
               FTP_Init,           //  initialize some variables
               FTP_Client,         //  wait for client connection
               FTP_User,           //  wait for user name
               FTP_Pass,           //  wait for user password
               FTP_Cmd };          //  answers to commands
 
 enum ftpTransfer { FTP_Close = 0, // In this stage, close data channel
                    FTP_Retrieve,  //  retrieve file
                    FTP_Store,     //  store file
                    FTP_List,      //  list of files
                    FTP_Nlst,      //  list of name of files
                    FTP_Mlsd };    //  listing for machine processing
 
 enum ftpDataConn { FTP_NoConn = 0,// No data connection
                    FTP_Pasive,    // Passive type
                    FTP_Active };  // Active type
 
 enum FtpOperation {
       FTP_CONNECT,
       FTP_DISCONNECT,
       FTP_FREE_SPACE_CHANGE
 };
 
 enum FtpTransferOperation {
       FTP_UPLOAD_START = 0,
       FTP_UPLOAD = 1,
 
       FTP_DOWNLOAD_START = 2,
       FTP_DOWNLOAD = 3,
 
 
       FTP_TRANSFER_STOP = 4,
       FTP_DOWNLOAD_STOP = 4,
       FTP_UPLOAD_STOP = 4,
 
       FTP_TRANSFER_ERROR = 5,
       FTP_DOWNLOAD_ERROR = 5,
       FTP_UPLOAD_ERROR = 5
 };
 
 class FtpServer
 {
 public:
   FtpServer( uint16_t _cmdPort = FTP_CMD_PORT, uint16_t _pasvPort = FTP_DATA_PORT_PASV );
 
   void    begin( const char * _user, const char * _pass, const char * welcomeMessage = "Welcome to Simply FTP server" );
   void    begin( const char * welcomeMessage = "Welcome to Simply FTP server" );
 
   void 	  end();
   void 	  setLocalIp(IPAddress localIp);
   void    credentials( const char * _user, const char * _pass );
   uint8_t handleFTP();
 
     void setCallback(void (*_callbackParam)(FtpOperation ftpOperation, unsigned int freeSpace, unsigned int totalSpace) )
     {
         _callback = _callbackParam;
     }
 
     void setTransferCallback(void (*_transferCallbackParam)(FtpTransferOperation ftpOperation, const char* name, unsigned int transferredSize) )
     {
         _transferCallback = _transferCallbackParam;
     }
 
 private:
   void (*_callback)(FtpOperation ftpOperation, unsigned int freeSpace, unsigned int totalSpace){};
   void (*_transferCallback)(FtpTransferOperation ftpOperation, const char* name, unsigned int transferredSize){};
 
   void    iniVariables();
   void    clientConnected();
   void    disconnectClient();
   bool    processCommand();
   bool    haveParameter();
   int     dataConnect( bool out150 = true );
   bool    dataConnected();
   bool    doRetrieve();
   bool    doStore();
   bool    doList();
   bool    doMlsd();
   void    closeTransfer();
   void    abortTransfer();
   bool    makePath( char * fullName, char * param = NULL );
   bool    makeExistsPath( char * path, char * param = NULL );
   bool    openDir( FTP_DIR * pdir );
   bool    isDir( char * path );
   uint8_t getDateTime( char * dt, uint16_t * pyear, uint8_t * pmonth, uint8_t * pday,
                        uint8_t * phour, uint8_t * pminute, uint8_t * second );
   char *  makeDateTimeStr( char * tstr, uint16_t date, uint16_t time );
   bool    timeStamp( char * path, uint16_t year, uint8_t month, uint8_t day,
                      uint8_t hour, uint8_t minute, uint8_t second );
   bool    getFileModTime( char * path, uint16_t * pdate, uint16_t * ptime );
 #if STORAGE_TYPE != STORAGE_FATFS
   bool    getFileModTime( uint16_t * pdate, uint16_t * ptime );
 #endif
   int32_t readChar();
 
   const String getFileName(FTP_FILE *file){
        return String(file->name());
   }
   bool     exists( const char * path ) {
 #if STORAGE_TYPE == (STORAGE_TYPE == STORAGE_SD && FTP_SERVER_NETWORK_TYPE == NETWORK_ESP8266_242)
       if (strcmp(path, "/") == 0) return true;
 #endif
       return STORAGE_MANAGER.exists( path );
   };
   bool     remove( const char * path ) { return STORAGE_MANAGER.remove( path ); };
   bool     makeDir( const char * path ) { return STORAGE_MANAGER.mkdir( path ); };
   bool     removeDir( const char * path ) { return STORAGE_MANAGER.rmdir( path ); };
 
 #if (STORAGE_TYPE == STORAGE_SD || STORAGE_TYPE == STORAGE_SD_MMC) && !defined(ESP32)
   bool     rename( const char * path, const char * newpath );
 #else
   bool     rename( const char * path, const char * newpath ) { return STORAGE_MANAGER.rename( path, newpath ); };
 #endif
 #if (STORAGE_TYPE == STORAGE_SD && defined(ESP8266))
   bool openFile( char path[ FTP_CWD_SIZE ], int readTypeInt );
 #else
   bool openFile( char path[ FTP_CWD_SIZE ], const char * readType );
   bool openFile( const char * path, const char * readType );
 #endif
   uint32_t fileSize( FTP_FILE & file );
 
 #if STORAGE_TYPE == STORAGE_SD || STORAGE_TYPE == STORAGE_SD_MMC
   uint32_t capacity() { return true; };
   uint32_t free() { return true; };
 #endif
     bool    legalChar( char c ) // Return true if char c is allowed in a long file name
     {
         if( c == '"' || c == '*' || c == '?' || c == ':' ||
             c == '<' || c == '>' || c == '|' )
           return false;
    return 0x1f < c && c < 0x7f;
     }
 
   IPAddress   localIp;                // IP address of server as seen by clients
   IPAddress   dataIp;                 // IP address of client for data
   FTP_SERVER_NETWORK_SERVER_CLASS  ftpServer;
   FTP_SERVER_NETWORK_SERVER_CLASS  dataServer;
   FTP_CLIENT_NETWORK_CLASS  client;
   FTP_CLIENT_NETWORK_CLASS  data;
   FTP_FILE     file;
   FTP_DIR      dir;
   ftpCmd      cmdStage;               // stage of ftp command connection
   ftpTransfer transferStage;          // stage of data connection
   ftpDataConn dataConn;               // type of data connection
   bool anonymousConnection = false;
   uint8_t  __attribute__((aligned(4))) // need to be aligned to 32bit for Esp8266 SPIClass::transferBytes()
            buf[ FTP_BUF_SIZE ];       // data buffer for transfers
   char     cmdLine[ FTP_CMD_SIZE ];   // where to store incoming char from client
   char     cwdName[ FTP_CWD_SIZE ];   // name of current directory
   char     rnfrName[ FTP_CWD_SIZE ];  // name of file for RNFR command
   const char *   user;     // user name
   const char *   pass;     // password
   char     command[ 5 ];              // command sent by client
   bool     rnfrCmd;                   // previous command was RNFR
   char *   parameter;                 // point to begin of parameters sent by client
   const char *   welcomeMessage;
   uint16_t cmdPort,
            pasvPort,
            dataPort;
   uint16_t iCL;                       // pointer to cmdLine next incoming char
   uint16_t nbMatch;
 
   uint32_t millisDelay,               //
            millisEndConnection,       //
            millisBeginTrans,          // store time of beginning of a transaction
            bytesTransfered,
            restartPos;           //
 };
 
 #endif // FTP_SERVER_H