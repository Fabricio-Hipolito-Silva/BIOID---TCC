#ifndef CADASTRO_H
#define CADASTRO_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>


extern Adafruit_Fingerprint finger;
extern uint8_t id;


bool cadastroDedo();

#endif
