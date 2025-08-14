#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <LiquidCrystal_I2C.h>

// Definir o objeto mySerial (com a UART2)
extern HardwareSerial mySerial;  // Declaração externa

// Definir o objeto finger
extern Adafruit_Fingerprint finger;  // Declaração externa

//Definir o LCD
extern LiquidCrystal_I2C lcd; // Endereço 0x27, LCD 16x2; //Declaração externa


void inicializarSensor();  // Função para inicializar o sensor de digital
void conectarWifi();
void inicializarTelaLCD();
void inicializarTecladoMatriz();


#endif
