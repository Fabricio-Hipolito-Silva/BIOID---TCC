#ifndef VALIDAR_H
#define VALIDAR_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HTTPClient.h>



extern Adafruit_Fingerprint finger;
extern uint8_t id;

int validarID();
String ValidarNome(int idV);
void validarSetup();
void validarLoop();



#endif
