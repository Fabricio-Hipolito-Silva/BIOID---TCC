#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>

// Definir o objeto mySerial (com a UART2)
extern HardwareSerial mySerial;  // Declaração externa

// Definir o objeto finger
extern Adafruit_Fingerprint finger;  // Declaração externa

void inicializarSensor();  // Função para inicializar o sensor de digital
void conectarWifi();

#endif
