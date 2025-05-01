#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include "fingerprint_init.h"

int ValidarID();

void setup() {
    Serial.begin(9600);
    inicializarSensor();
}

void loop(){
    
    uint8_t idDigital = ValidarID();
    if (idDigital >= 0) {
        Serial.print("ID validada com sucesso: ");
        Serial.println(idDigital);
    } else {
        Serial.println("ID não reconhecida.");
    }
    }

int ValidarID() {
    int p;
    while ((p = finger.getImage()) != FINGERPRINT_OK);

    if (finger.image2Tz(1) != FINGERPRINT_OK) return -1;

    Serial.println("Imagem capturada. Retire o Dedo");
    delay(1000);

    while (finger.getImage() != FINGERPRINT_NOFINGER);

    p = finger.fingerSearch();
    if (p == FINGERPRINT_OK) {
        return finger.fingerID;
    } else {
        return -1;
    }
}
