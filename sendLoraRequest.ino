void sendLoraRequest(String request)
{
  String dest_string;
  byte destination = 0x00;
  dest_string = request.substring(0,2);
  destination = dest_string.toInt();
  //Serial.print("Destination as byte:");
  //Serial.println(destination,HEX);
  sendLoraMessage(request,destination);
}
