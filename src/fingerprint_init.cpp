#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WebSocketsClient.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "secret.h"
#include "fingerprint_init.h"


HardwareSerial mySerial(2);  // Define mySerial na UART2 (RX = 13, TX = 12)
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço 0x27, LCD 16x2
WebSocketsClient webSocket;



void inicializarTelaLCD(){
  Wire.begin(18,19);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,1);
}

void inicializarTecladoMatriz(){
  const byte LINHAS = 4;
  const byte COLUNAS = 3;
  char teclas[LINHAS][COLUNAS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
  };
  byte pinosLinhas[LINHAS] = {13, 12, 14, 27};
  byte pinosColunas[COLUNAS] = {26, 25, 33};
  Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);
  Serial.begin(9600);
}

void inicializarSensor() {
  mySerial.begin(57600, SERIAL_8N1, 4, 5); 

  finger.begin(57600);
  if (finger.verifyPassword() == FINGERPRINT_OK) {
    lcd.setCursor(0,0);
    lcd.print("Sensor");
    lcd.setCursor(0,1);
    lcd.print("Encontrado");
      return;
  } else {
    lcd.setCursor(0,0);
    lcd.print("Sensor não");
    lcd.setCursor(0,1);
    lcd.print("Encontrado");
    ESP.restart();
  }
}

void conectarWifi(){
  WiFi.begin(ssid, senha);
  int ponto = 0;
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Conectando");
    
    // Adiciona pontinhos como efeito
    for(int i = 0; i < ponto; i++){
      lcd.print(".");
    }

    ponto++;
    if(ponto > 3) ponto = 0; // Reseta após 3 pontos

    delay(500);
    };
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Conectado");
  lcd.setCursor(0,1);
  lcd.print("IP:");
  lcd.setCursor(4,1);
  lcd.print(WiFi.localIP());
};

void inicializarWebSocket(){
    webSocket.begin(Server, 8080, "/");
    webSocket.onEvent(webSocketEvent);
};

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("WS Desconectado");
            delay(1000);
            lcd.clear();
            Serial.println("WebSocket Disconnected");
            break;
        case WStype_CONNECTED:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("WS conectado");
            delay(1000);
            lcd.clear();
            Serial.println("WebSocket Connected");
            webSocket.sendTXT("Hello Server");
            break;
        case WStype_TEXT:
            delay(1000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("WS Mensagem:");
            lcd.setCursor(0,1);
            lcd.print((char *)payload);
            delay(1000);
            lcd.clear();
            Serial.printf("WebSocket Message: %s\n", payload);
            break;
    }
}




