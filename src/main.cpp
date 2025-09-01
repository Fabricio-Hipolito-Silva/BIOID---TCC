#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WebSocketsClient.h>
#include "cadastro.h"
#include "validar.h"
#include "fingerprint_init.h"


void setup(){
    //cadastroSetup();
    validarSetup();  
}void loop(){
    //cadastroLoop();
    webSocket.loop();
    validarLoop(); 
}