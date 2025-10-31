#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Adafruit_Fingerprint.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <Keypad.h>
#include "bioID_init.h"
#include "secret.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address
HardwareSerial mySerial(2); // Use UART2
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
WebSocketsClient webSocket;
Keypad* teclado;
String rmDigitado;
bool modoDigitacaoRM;

void apagarTodasDigitais() {
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Apagando tudo...");
  delay(1000);

  // Comando especial: apaga TODO o banco do sensor
  int p = finger.emptyDatabase();

  lcd.clear();
  if (p == FINGERPRINT_OK) {
    lcd.print("Banco limpo!");
    Serial.println("Todas as digitais foram apagadas com sucesso.");
  } else {
    lcd.print("Erro!");
    Serial.print("Falha ao apagar digitais. Codigo: ");
    Serial.println(p);
  }

  delay(2000);
};

void inicializar_LCD() {
  Wire.begin(18,19);                  // Initialize I2C communication
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);            // Set cursor to first column, first row
};

void inicializar_Fingerprint() {
  mySerial.begin(57600, SERIAL_8N1, 4, 5);           // Start serial communication at 57600 baud
  finger.begin(57600);     
  uint8_t p = finger.getParameters();
if (p == FINGERPRINT_OK) {
    Serial.println("Sensor respondeu! Endereço e parâmetros OK");
} else {
    Serial.print("Erro no sensor: "); Serial.println(p);
}        // Initialize fingerprint sensor
  if (finger.verifyPassword()) {   // Verify password     
    lcd.setCursor(0, 0);
    lcd.print("Sensor OK");
    delay(1000);
    lcd.clear();
    Serial.println("Testando slots salvos...");
for (int i = 1; i < 10; i++) {
  int res = finger.loadModel(i);
  if (res == FINGERPRINT_OK) {
    Serial.print("Slot ");
    Serial.print(i);
    Serial.println(" ocupado");
  } else {
    Serial.print("Slot ");
    Serial.print(i);
    Serial.println(" vazio");
  }
}

    // apagarTodasDigitais(); // Apaga todas as digitais ao iniciar
    
    


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
  teclado = new Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);
  rmDigitado = "";
  modoDigitacaoRM = false;
};


void inicializar_BIOID() {
  inicializar_LCD();
  inicializar_Fingerprint();
  conectar_WIFI();
  inicializarTecladoMatriz();

  webSocket.begin(server, 8080, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000); // Attempt to reconnect every 5 seconds
};