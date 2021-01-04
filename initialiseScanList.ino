void initaliseScanList()
{
  //Serial.println("initialiseScanList");
  //sensors.addSensor(0,"01"); // Trough 1
  //sensors.addSensor(1,"04"); // Trough 2
  //sensors.addSensor(2,"08"); // Trough 2
  for (int i = 0; i < configuration.scanListLength; i++)
  {
    #ifdef debug
    Serial.println("Adding sensor:");
    Serial.print(configuration.scanList[i].loraID);
    Serial.print(",");
    Serial.print(configuration.scanList[i].deviceType);
    Serial.print(":");
    #endif
    sensors.addSensor(i, configuration.scanList[i].loraID, configuration.scanList[i].deviceType);
  }
}
