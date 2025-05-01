#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include "cadastro.h"
#include "fingerprint_init.h"
uint8_t id;


void cadastroSetup() {
  Serial.begin(9600);
  inicializarSensor();
}

void cadastroLoop() {
  Serial.println("\nDigite o ID (de 1 a 127) para o novo cadastro:");
  while (Serial.available() == 0);
  id = Serial.parseInt();
  Serial.print("Registrando nova digital com ID ");
  Serial.println(id);

  Serial.println("Coloque o dedo no sensor...");
  while (!cadastroDedo());
  Serial.println("Cadastro concluído!");
  delay(3000);
}

