#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include "secret.h"
#include "fingerprint_init.h"


HardwareSerial mySerial(2);  // Define mySerial na UART2 (RX = 13, TX = 12)
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);  // Inicializa o sensor de digital

void inicializarSensor() {
  Serial.begin(9600);
  mySerial.begin(57600, SERIAL_8N1, 13, 12); 

  finger.begin(57600);
  if (finger.verifyPassword() == FINGERPRINT_OK) {
    Serial.println("Sensor encontrado e senha correta!");
    return;
  } else {
    Serial.println("Sensor não encontrado ou senha incorreta!");
    ESP.restart();
  }
}

void conectarWifi(){
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print('.');
  };
  Serial.println("");
  Serial.println("Conectado");
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());
};


