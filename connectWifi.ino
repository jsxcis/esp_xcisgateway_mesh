boolean connectWifi()
{
   // Connect to WiFi network
  #ifdef debug
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println(password);
  #endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  WiFi.config(staticIP, gateway, subnet);

   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
   /* 
  if(!testWifi())
  {
        WiFi.disconnect(true);
        WiFi.setAutoReconnect(false);
        WiFi.mode(WIFI_OFF);
        networkState = false;
        return false;
  } 
  // Print the IP address
  #ifdef debug
  Serial.print("Network IP Address:");
  Serial.println(WiFi.localIP());
  #endif
  if (WiFi.status() == WL_CONNECTED)
  {
    #ifdef debug
    Serial.println("Connected and monitoring");
    #endif
    digitalWrite(UPLINK, LOW);//ON

    networkState = true;
    return true;
  }
  networkState = false;
  return false;
  */
}
bool testWifi(void)
{
  int c = 0;
  #ifdef debug
  Serial.println("Waiting for Wifi to connect");  
  #endif
  while ( c < 20 )
  {
    digitalWrite(UPLINK, LOW);//ON
    if (WiFi.status() == WL_CONNECTED)
    {
      #ifdef debug
      Serial.println(WiFi.status());
      #endif
      digitalWrite(UPLINK, LOW);//ON
      return true;
    } 
    delay(500);
    #ifdef debug
    Serial.print(WiFi.status());
    #endif
    c++;
    digitalWrite(UPLINK, HIGH);//ON
  }
  #ifdef debug
  Serial.println("");
  #endif
  return false;
}
