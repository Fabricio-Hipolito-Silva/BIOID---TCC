#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include "cadastro.h"


HardwareSerial mySerial(2); // UART2 (13 = RX, 12 = TX)
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;


void setup() {
  Serial.begin(9600);
  mySerial.begin(57600, SERIAL_8N1, 13, 12); // Inicia UART2
  delay(100);

  finger.begin(57600);
  if (finger.verifyPassword() == FINGERPRINT_OK) {
    Serial.println("Sensor encontrado e senha correta!");
  } else {
    Serial.println("Sensor não encontrado ou senha incorreta!");
    ESP.restart();
  }
}

void loop() {
  
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

