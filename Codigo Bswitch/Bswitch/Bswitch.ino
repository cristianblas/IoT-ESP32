#include <ESPAsyncTCP.h>
#include <painlessMesh.h>
#include "IPAddress.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

painlessMesh  mesh;
IPAddress myAPIP(0,0,0,0);

void setup() {
  Serial.begin(115200);         
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 6 );
  mesh.onReceive(&receivedCallback);
  // This node and all other nodes should ideally know the mesh contains a root, so call this on all nodes
  mesh.setContainsRoot(true);
  delay(500);
  myAPIP = IPAddress(mesh.getAPIP());
  Serial.println("Mi AP IP es " + myAPIP.toString());
}

void loop() {
  mesh.update();
}

void receivedCallback( const uint32_t &from, const String &msg ) {
  Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
  String led;
  led=msg.c_str();
  if(led=="ON2"){
  digitalWrite(2, LOW);     
  }
  if(led=="OFF2"){
  digitalWrite(2, HIGH);     
  }
}

IPAddress getlocalIP() {
  return IPAddress(mesh.getStationIP());
}
