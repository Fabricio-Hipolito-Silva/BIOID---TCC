#ifndef CADASTRO_H
#define CADASTRO_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HTTPClient.h>
#include "secret.h"



extern Adafruit_Fingerprint finger;
extern uint8_t id;
extern String nome;


bool cadastroDedo();
void cadastroSetup();  // Declaração da função de setup
void cadastroLoop(); 

#endif
