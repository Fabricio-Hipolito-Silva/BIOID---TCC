#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include "fingerprint_init.h"
#include "validar.h"

int ValidarID();

void validarSetup() {
    Serial.begin(9600);
    inicializarSensor();
    conectarWifi();
}

void validarLoop(){
    
    int idDigital = ValidarID();
    if (idDigital >= 0) {
        Serial.print("ID validada com sucesso: ");
        Serial.println(idDigital);
    } else {
        Serial.println("ID não reconhecida.");
    }
    }

