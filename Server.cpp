// servidor y vinculacion a la Red//
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <EEPROM.h>


////////////////////////////////
//Conexion WiFi Y Servidor web//
////////////////////////////////

String SerialNumber ="";
AsyncWebServer server(80);



void setup_Server(){

  if (!MDNS.begin("esp32")) {                 //nombre del dominio ->esp32.local/
    Serial.println("MDNS fallo!");
    return;
  }
  Serial.println("mDns Comenzo : esp32.local/");
  
////////////////////////////////////////////
// rutas del servidor para las peticiones //
////////////////////////////////////////////


 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(200, "text/plain", 
                    "Bionic House Control");
});

 server.on("/mac", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(200, "text/plain", 
                    "Serial: "  + SerialNumber);
});


/////////////////////////////////////////////
/////////////////////////////////////////////
  server.begin();                             //Servidor Enable
  MDNS.addService("http","tcp",80);
}




void serialMac() {
  for (int i=0;i<=4;i++){
    SerialNumber += EEPROM.read(i);
  }
  Serial.print("Mac del DCPO: ");
  Serial.println(SerialNumber);
}
/*
void Cuarto (){
  //String data = server.arg(data);
  StaticJsonBuffer<200> jBuffer;
  //JsonObject& jObject = jBuffer.parseObject(data);
  JsonObject& jObject = jBuffer.parseObject(server.argName(1));
  //jObject.printTo(Serial);
  String ud = server.argName(0);
  String id = server.arg(0);
  String state = server.arg(1);
  String state1= server.argName(1);
  Serial.println(ud + "=" + id);
  Serial.println(state1 + "=" + state);
  Serial.println("------------------------");
  if(state == "1" ){
    digitalWrite(0,HIGH);
    Serial.println("Luz Apagada");
  }else if (state == "0"){
    digitalWrite(0,LOW);
    Serial.println("Luz Encendida");
  }
 
 server.send(200);
}
*/
