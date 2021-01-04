String readResponse()
{
  String msg = "";
  char character;

  while(Serial.available()) {
      character = Serial.read();
      msg.concat(character);
  }
    #ifdef debug
    Serial.print("ESP Received: ");
    Serial.println(msg);
    #endif
    return msg;
}
