// Main Principal
#include <FS.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "Server.h"               //Archivo Server y WiFi
#include "Mesh.h"


#define EEPROM_SIZE 5
const char mac[]={'A','G','H','C','X'};


void setup() {
  delay(100);
  Serial.begin(115200);            //Velocidad Tx
  EEPROM.begin(EEPROM_SIZE);       //inicializo los 5 byte para alamcenar
  setup_mesh();
  setup_Server();                  //Servidor y Wifi Server.cpp
  //serial();                      //escribir el serial del DCPO
  serialMac();                     //SerialNumber ==> para poder acceder al DCPO
  
  
}
void loop() {
  loop_mesh();
}

void serial() {
  for (int i=0;i<=4;i++){
    EEPROM.write(i,mac[i]);
    EEPROM.commit();
  }
}
