#ifndef VALIDAR_H
#define VALIDAR_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>


extern Adafruit_Fingerprint finger;
extern uint8_t id;

int validarID();
void validarSetup();
void validarLoop();



#endif
