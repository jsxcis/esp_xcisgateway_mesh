void launchWeb(int webtype)
{
  #ifdef debug
  Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.print("Local IP: ");
  //Serial.println(WiFi.localIP());
  #endif
  createWebServer(webtype);
  // Start the server
  server->begin();
  #ifdef debug
  Serial.println("Server started"); 
  #endif
}
