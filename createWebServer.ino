void createWebServer(int webtype)
{

  if ( webtype == 1 )
  {
    #ifdef debug
      Serial.println("Running AP website");
     #endif
      server->on("/", []()
      {
          String content;
          content = "test page";
          server->send(200, "text/html", content);
      });  
  }
  else if (webtype == 0) 
  {
     server->on("/", []()
      {
       
          String content;
          #ifdef debug
          Serial.println("test page");
          #endif
          //content ="Received:" + responseData;
          content ="test page" + String(loopCount);
          loopCount++;
          server->send(200, "text/plain", content);
      });
      server->on("/dataResponse", []()
      {
          String content;
          #ifdef debug
          Serial.println("dataResponse Request");
          #endif
          String response = "";
          response = processRequest();
          #ifdef debug
          Serial.println(response);
          #endif
          server->send(200, "text/plain", response);
      });
      server->on("/displaySensors", []()
      {
          String content;
          #ifdef debug
          Serial.println("displaySensors Request");
          #endif
          String response = "Display Sensors\n";
          response += sensors.listSensors(true);
          #ifdef debug
          Serial.println(response);
          #endif
          server->send(200, "text/plain", response);
      });
      server->on("/displayStatus", []()
      {
          String content;
          #ifdef debug
          Serial.println("displayStatus Request");
          #endif
          String response = "Display Status\n";
          response += displayStatus();
          #ifdef debug
          Serial.println(response);
          #endif
          server->send(200, "text/plain", response);
      });
  }
}
