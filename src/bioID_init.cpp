#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Adafruit_Fingerprint.h>
#include <WebSocketsClient.h>
#include "secret.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address
HardwareSerial mySerial(2); // Use UART2
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
WebSocketsClient webSocket;

void inicializar_LCD() {
  Wire.begin(18,19);                  // Initialize I2C communication
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);            // Set cursor to first column, first row
};

void inicializar_Fingerprint() {
  mySerial.begin(57600, SERIAL_8N1, 4, 5);           // Start serial communication at 57600 baud
  finger.begin(57600);             // Initialize fingerprint sensor
  if (finger.verifyPassword()) {   // Verify password
    lcd.setCursor(0, 0);
    lcd.print("Sensor OK");
    delay(1000);
    lcd.clear();
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Sensor ERRO");
    while (1) {             
      esp_restart();    // Halt if sensor is not found
      delay(1);
    }
  }
}

void conectar_WIFI(){
    WiFi.begin(ssid, senha);         // Connect to Wi-Fi network
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Conectando...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        lcd.print(".");
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Conectado");
    delay(1000);
    lcd.clear();
};

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket Connected");
      break;
    case WStype_TEXT:
      Serial.printf("WebSocket Message: %s\n", payload);
      // Handle incoming messages here
      break;
    case WStype_BIN:
      Serial.println("WebSocket Binary Message");
      break;
    case WStype_ERROR:
      Serial.println("WebSocket Error");
      break;
    case WStype_PING:
      // Handle ping if necessary
      break;
    case WStype_PONG:
      // Handle pong if necessary
      break;
  }
}

void inicializar_BIOID() {
  inicializar_LCD();
  inicializar_Fingerprint();
  conectar_WIFI();

  webSocket.begin(server, 8080, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000); // Attempt to reconnect every 5 seconds
};





