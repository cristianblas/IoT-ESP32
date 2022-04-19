// Mesh y vinculacion a la Red de los nodos//
#include <painlessMesh.h>
#include "IPAddress.h"

#define   ID_Mesh     "whateverYouLike"
#define   Clave_Mesh   "somethingSneaky"
#define   Puerto_Mesh       5555

#define   ID_Wifi    "BLAS"
#define   Clave_Wifi "b214135713"
#define HOSTNAME "HTTP_BRIDGE"
void receivedCallback( const uint32_t &from, const String &msg );
painlessMesh  mesh;             //Instancia de la clase mesh.cpp
IPAddress getlocalIP();
IPAddress miIP(0,0,0,0);
IPAddress myAPIP(0,0,0,0);

void setup_mesh(){
   delay(400);
  //  Iniciando la Red Mesh
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  
  mesh.init( ID_Mesh, Clave_Mesh, Puerto_Mesh, WIFI_AP_STA, 6 );
  mesh.onReceive(&receivedCallback);
  mesh.stationManual(ID_Wifi, Clave_Wifi);
  mesh.setHostname(HOSTNAME);

  mesh.setRoot(true);                 // Puente Nodo Solo usa el Nodo Central
  mesh.setContainsRoot(true);         // Todos los Nodos 
  myAPIP = IPAddress(mesh.getAPIP());
  delay(500);
  Serial.println("Mi AP IP es " + myAPIP.toString());
}
void loop_mesh(){
  mesh.update();
  if(miIP != getlocalIP()){
    miIP = getlocalIP();
    Serial.println("Mi IP es " + miIP.toString());
  }

}

/// Metodos plus para instancias de la mesh control de realimentacion
/// recibir iplocal de la mesh
void receivedCallback( const uint32_t &from, const String &msg ) {
 Serial.printf("Puente: Recivido de %u msg=%s\n", from, msg.c_str());
}

IPAddress getlocalIP() {
  return IPAddress(mesh.getStationIP());
}
