#include <XcisSensor.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LoRa.h>
#include "EEPROMAnything.h"

#define debug

ESP8266WebServer *server;

int loopCount = 0;


//const char *ssid = "Buffalo-G-A5F8";
//const char *password = "bvvved6gfgfar";
//IPAddress staticIP(10,141,109,50);
//IPAddress gateway(10,141,108,1);  
//IPAddress subnet(255,255,252,0);
const char *ssid = "sharpnet";
const char *password = "0294400648";
IPAddress staticIP(192,168,0,52);
IPAddress gateway(192,168,0,1);  
IPAddress subnet(255,255,255,0);

#define UPLINK 0

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xFF;     // address of this device
boolean networkState = false;

void(* resetFunc)(void) = 0;

unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish
unsigned long DELAY_TIME = 10000; // Scan Rate
unsigned long delayOnlineCheckStart = 0; // the time the delay started
bool delayOnlineCheck = false;
unsigned long CHECK_ONLINE_TIME = 60000; // 2 * 60000msec

XcisSensor sensors;

char inChar; // Where to store the character read
String buffer;

struct sensor
{
  char loraID[16];
  char deviceType[16];
};

struct config_t
{
    boolean changeFlag;
    char gatewayName[64] = "";
    char ssid[32] = "";
    char pkey[64] = "";
    char softssid[32] = "XCIS_Sensor_Dev";
    char softpkey[64] = "xcis12345";
    char userName[10] = "";
    char password[10] = "";
    boolean staticIPFlag;
    char staticIP[32];
    char gateway[32];
    char mac[32];
    char subnet[32];
    char dns1[32];
    char portNumber[32];
    sensor scanList[64];
    int scanListLength;
    unsigned long scanRate;
} configuration;
 
//=======================================================================
void checkOnline()
{
  #ifdef debug
  Serial.println("CheckOnline-------------------------------------");
  #endif
  sensors.checkSensorsOnline();
}
String response = "NULL";
void scanSensors()
{
  #ifdef debug
  Serial.println("scanSensors-------------------------------------");
  #endif
    int sensorToScan = sensors.scanNextSensor();
    if (sensorToScan != -1)
    {
      String req = sensors.getSensorLoraID(sensorToScan) + ":REQUEST:D25:EOM";
      Serial.print(req); // For sending via MEGA
      onReceive();
      //digitalWrite(UPLINK, LOW);//ON
      //sendLoraRequest(req);
      //digitalWrite(UPLINK, HIGH);//OFF
    }
  //digitalWrite(UPLINK, LOW);//ON
  #ifdef debug
  Serial.println("scanSensors done");
  #endif
}

void setup()
{
    //pinMode(UPLINK, OUTPUT);
    //digitalWrite(UPLINK, HIGH);
    //Serial.begin(115200);
    //Serial.println();
    //Serial.flush();
    //Serial.end();
    //delay(100);
    Serial.begin(115200);
    #ifdef debug
    Serial.printf("\n\nSdk version: %s\n", ESP.getSdkVersion());
    Serial.printf("Core Version: %s\n", ESP.getCoreVersion().c_str());
    Serial.printf("Boot Version: %u\n", ESP.getBootVersion());
    Serial.printf("Boot Mode: %u\n", ESP.getBootMode());
    Serial.printf("CPU Frequency: %u MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Flash Chip Size: %s\n", String(ESP.getFlashChipSize()).c_str());
    #endif
    rst_info* rinfo = ESP.getResetInfoPtr();
    #ifdef debug
    Serial.printf("rinfo->reason:   %d, %s\n", rinfo->reason, ESP.getResetReason().c_str());
    #endif
    EEPROM.begin(4096);
    setDefaults();
    setDefaultScanlist();
    readConfiguration();
    #ifdef debug
    displayConfiguration();
    #endif


    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    //WiFi.config(staticIP, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      #ifdef debug
      Serial.print(".");
     #endif
    }
  

  #ifdef debug
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  #endif
  
    server = new ESP8266WebServer(80);
    launchWeb(0);
    
    //LoRa.setPins(4,5,2);
    //if (!LoRa.begin(915E6)) // initialize ratio at 915 MHz
    //{             
    //  Serial.println("LoRa init failed. Check your connections.");
    //}
    //Serial.println("LoRa Gateway init succeeded.");
    //Serial.println("Ready");
    //delay(1000);
    initaliseScanList();
    sensors.listSensors(false);
    
    delayStart = millis();   // start delay
    delayRunning = true; // not finished yet
    delayOnlineCheckStart = millis();
    delayOnlineCheck = true;
    
}
void loop()
{
  /*
   // check if online check delay has timed out after Xsec == CHECK_ONLINE_TIME
  if (delayOnlineCheck && ((millis() - delayOnlineCheckStart) >= CHECK_ONLINE_TIME))
  {
    delayOnlineCheckStart += CHECK_ONLINE_TIME; 
    //delayRunning = false; // // prevent this code being run more then once
    checkOnline();
  }
  // check if scan delay has timed out after Xsec == configuration.scanRate
  if (delayRunning && ((millis() - delayStart) >= configuration.scanRate))
  {
    delayStart += configuration.scanRate; 
    //delayRunning = false; // // prevent this code being run more then once
    scanSensors();
  }
  delay(100);
   */
  server->handleClient();
  //onReceive();
 

}
