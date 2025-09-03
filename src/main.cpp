#include <Arduino.h>
#include <WebSocketsClient.h>
#include "bioID_init.h"

void setup(){
inicializar_BIOID();
};
void loop(){
webSocket.loop();
};
