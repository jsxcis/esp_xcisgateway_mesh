void processCommand(String command)
{
  String dest_string;
  byte destination = 0x00;
  //Serial.print(command);
  //Serial3.write("Hello\n");
  dest_string = command.substring(0,2);
    
  //Serial.print("Destination as string:");
  //Serial.println(dest_string);

  destination = dest_string.toInt();

  //Serial.print("Destination as byte:");
  //Serial.println(destination,HEX);
  sendLoraMessage(command,destination);
}
