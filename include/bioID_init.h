#ifndef BIOID_INIT_H
#define BIOID_INIT_H

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Adafruit_Fingerprint.h>
#include <WebSocketsClient.h>

extern LiquidCrystal_I2C lcd;
extern HardwareSerial mySerial;
extern Adafruit_Fingerprint finger;
extern WebSocketsClient webSocket;
extern bool verificacaoAtiva;

void inicializar_BIOID();
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
bool cadastrarDigital(int rm, int slot);
void verificarDigitalStep();
// void validarDigital();
void iniciarVerificacao();
void pararVerificacao();
void apagarTodasDigitais();

#endif