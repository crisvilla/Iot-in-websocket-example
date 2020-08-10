/********ESP8266***********|
 *   Websocket example     |
 **************************/
 

 
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include "webserver.h"
 
WiFiServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
 

const byte output_pin[] = {16,0,2,14,12,13,15};  // output pins
bool load_status[] = {0,0,0,0,0,0};
 
 
char ssid[] = "yourSSID";
char pass[]= "yourSSIDpassword";
 
void setup()
{
  // initiate output pin and make it LOW after the initial startup
  for(int i=0;i<7;i++){
    pinMode(output_pin[i], OUTPUT);
    digitalWrite(output_pin[i], LOW);
  }
 
  Serial.begin(115200);
  Serial.println();
  Serial.println("Serial started at 115200");
  Serial.println();
 
  // Connect to a WiFi network
  Serial.print(F("Connecting to "));  Serial.println("ssid");
  WiFi.begin(ssid,pass);
 
 
 
 
  // try to connect(max = 17 tries)
  Serial.print("Connecting");
  int count = 0; 
  while ( (WiFi.status() != WL_CONNECTED) && count < 17){
    Serial.print(".");  delay(500);  count++;
  }
 
  if (WiFi.status() != WL_CONNECTED){ 
    Serial.println("");  Serial.print("Failed to connect to ");  Serial.println(ssid);
    while(1); // loop here if no connection to any known wifi
  }
 
  Serial.println("");
  Serial.println(F("[CONNECTED]"));
  Serial.print("[IP ");
  Serial.print(WiFi.localIP()); // this your local ip address that you need to put in you browser address bar
  Serial.println("]");
 
  // start a server
  server.begin();
  Serial.println("Server started");
 
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
 
}
 
 
void loop(){

    webSocket.loop();
 
    WiFiClient client = server.available();     // Check if a client has connected
    if (client){
      client.flush();
      client.print( header );
      client.print( html_1 ); 
      Serial.println("New page served");
      delay(5);
    }
 
    
}  // loop ends here
 
 
void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length){ // packet/stream event
  if(type == WStype_TEXT){
      
      load_status[payload[0] - 48] = payload[1] - 48;

      digitalWrite(output_pin[payload[0] - 48], load_status[payload[0] - 48]);
      webSocket.broadcastTXT(payload);
      Serial.print("payload=");
      Serial.print(payload[0] - 48);
      Serial.println(payload[1] - 48);
  }
 
  else 
  {
    Serial.print("WStype = ");   Serial.println(type);  
    Serial.print("WS payload = ");
    for(int i = 0; i < length; i++) { Serial.print((char) payload[i]); }
    Serial.println();
    for(int i=0;i<7;i++){
      String data = "";
      data = i;
      data = data + load_status[i];
      webSocket.broadcastTXT(data);
      Serial.println(data);
    }
  }
}
