#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include "BioID_init.h"

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected");
      break;

    case WStype_CONNECTED:
      Serial.println("WebSocket Connected");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Esperando cmd...");
      break;

    case WStype_TEXT: {
        String msg = String((char*)payload);
        Serial.println("Mensagem recebida do WS:");
        Serial.println(msg);

        StaticJsonDocument<200> doc; //Tem que Atualizar isso aqui depois
        deserializeJson(doc, msg);

        const char* action = doc["action"];
        int rm = doc["rm"];
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("RM: ");
        lcd.print(rm);

        if (strcmp(action, "cadastrar_digital") == 0) {
          // Serial.printf("Cadastrar digital para RM %d\n", rm);
          // lcd.setCursor(0, 1);
          // lcd.print("Cad. Digital");
          cadastrarDigital(rm);
        };  
        break;
      }

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
};
