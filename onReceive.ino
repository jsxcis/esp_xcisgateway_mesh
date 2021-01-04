bool onReceive()
{
  
    response = readResponse();
    //response = "ID=01,Name=Azabu,Value=100,";
    String loraID = response.substring(3,5);
    int scanID = sensors.getSensorScanNumber(loraID);
    sensors.setSensorData(scanID, response);
    sensors.setDeviceMode(scanID,"ONLINE",millis());
    /*
    if (response != "NULL")
    {
      sensors.setSensorData(sensorToScan, response);
      sensors.setDeviceMode(sensorToScan,"ONLINE",millis()); 
    }
    else
    {
      sensors.setSensorData(sensorToScan, String(sensorToScan));
      //sensors.setDeviceMode(sensorToScan,"OFFLINE",millis());
    }

    //int scanID = sensors.getSensorScanNumber(String(sender));
    //sensors.setSensorData(scanID, incoming);
    //sensors.setDeviceMode(scanID,"ONLINE",millis());
    //sensors.displaySensor(scanID);
    //digitalWrite(UPLINK, HIGH);//OFF
    */
  return true;
}
