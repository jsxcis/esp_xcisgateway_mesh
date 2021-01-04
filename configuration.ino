boolean configUpdate()
{
  //Serial.println("Processing Config change");
 
}
void setDefaults()
{
  //Serial.println("Setting Defaults");
  
  for (int i = 0; i< 4096; i++)
  {
    EEPROM.write(i,0);
  }
  EEPROM.commit();
  delay(100);
  configuration.changeFlag = true;
  strcpy(configuration.gatewayName,"DEFAULT");
  strcpy(configuration.ssid,"NOT_SET");
  strcpy(configuration.pkey,"NOT_SET");
  String ssidName = String("XCIS_Sensor_") + String(configuration.gatewayName);
  strcpy(configuration.softssid,ssidName.c_str());
  strcpy(configuration.softpkey,"xcis12345");
  strcpy(configuration.userName,"admin");
  strcpy(configuration.password,"admin");
  
  configuration.staticIPFlag = false;
  strcpy(configuration.staticIP,"NOT_SET");
  strcpy(configuration.gateway,"NOT_SET");
  strcpy(configuration.mac,"NOT_SET");
  strcpy(configuration.subnet,"NOT_SET");
  strcpy(configuration.dns1,"8.8.8.8");
  strcpy(configuration.portNumber,"80");
  configuration.scanListLength = 0;
  configuration.scanRate = 3000;
  
  EEPROM_writeAnything(0, configuration);
  EEPROM.commit();
}
void displayConfiguration() //debug
{
  Serial.println("Configuration");
  EEPROM_readAnything(0, configuration);
  Serial.print("Sensor name:");
  Serial.println(configuration.gatewayName); 
  Serial.print("change flag:");
  Serial.println(configuration.changeFlag);
  Serial.print("ssid:");
  Serial.println(configuration.ssid);
  Serial.print("pkey:");
  Serial.println(configuration.pkey);
  Serial.print("softssid:");
  Serial.println(configuration.softssid);
  Serial.print("softpkey:");
  Serial.println(configuration.softpkey);
  Serial.print("staticIP:");
  Serial.println(configuration.staticIP);
  Serial.print("port:");
  Serial.println(configuration.portNumber);
 
  Serial.print("username:");
  Serial.println(configuration.userName);
  Serial.print("password:");
  Serial.println(configuration.password);
  Serial.print("scan rate:");
  Serial.println(configuration.scanRate);
  
  for (int i = 0; i < configuration.scanListLength; i++)
  {
    Serial.print(configuration.scanList[i].loraID);
    Serial.print(",");
    Serial.print(configuration.scanList[i].deviceType);
    Serial.print(":");
  }
  Serial.println("End configuration");
}
void readConfiguration()
{
  EEPROM_readAnything(0, configuration);
}

void setDefaultScanlist()
{
  #ifdef debug
  Serial.println("Setting Default ScanList");
  #endif
  // setup scanlist
  strcpy(configuration.scanList[0].loraID, "01");
  strcpy(configuration.scanList[0].deviceType, "Trough");
  strcpy(configuration.scanList[1].loraID, "02");
  strcpy(configuration.scanList[1].deviceType, "Trough");
  strcpy(configuration.scanList[2].loraID, "03");
  strcpy(configuration.scanList[2].deviceType, "Trough");
  strcpy(configuration.scanList[3].loraID, "08");
  strcpy(configuration.scanList[3].deviceType, "Trough");  configuration.scanListLength = 4;
  
  EEPROM_writeAnything(0, configuration);
  EEPROM.commit();
}
