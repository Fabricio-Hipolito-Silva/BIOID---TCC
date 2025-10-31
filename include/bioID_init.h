#ifndef BIOID_INIT_H
#define BIOID_INIT_H

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Adafruit_Fingerprint.h>
#include <WebSocketsClient.h>
#include <Keypad.h>

extern LiquidCrystal_I2C lcd;
extern HardwareSerial mySerial;
extern Adafruit_Fingerprint finger;
extern WebSocketsClient webSocket;
extern bool verificacaoAtiva;
extern Keypad* teclado;
extern String rmDigitado;
extern bool modoDigitacaoRM;


void inicializar_BIOID();
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
bool cadastrarDigital(int rm, int slot);
void verificarDigitalStep();
void verificarTeclado();
void iniciarVerificacao();
void pararVerificacao();
void apagarTodasDigitais();
bool atualizarDigital(int rm, int slot);

#endif