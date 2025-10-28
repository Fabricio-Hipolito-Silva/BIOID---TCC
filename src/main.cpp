#include <Arduino.h>
#include <WebSocketsClient.h>
#include "bioID_init.h"

void setup(){
Serial.begin(9600); 
inicializar_BIOID();

};
void loop(){
webSocket.loop();
  if (verificacaoAtiva) {
    verificarDigitalStep();
  }
};
