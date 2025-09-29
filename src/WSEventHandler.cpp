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

      if(doc.containsKey("action")){
       const char* action = doc["action"];
        if (strcmp(action, "cadastrar_digital") == 0) {
          int rm = doc["rm"];
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("RM: ");
          lcd.print(rm);
          cadastrarDigital(rm);
        }else if(strcmp(action, "validar_digital") == 0){
        iniciarVerificacao();
        validarDigital();
      }
      }else if(doc.containsKey("status")){
          const char* status = doc["status"];
          if (strcmp(status, "sucesso") == 0) {
            Serial.println(status);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Cadastrado");
            lcd.setCursor(0, 1);
            lcd.print("com Sucesso");
            delay(1500);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Esperando cmd...");

          } else if (strcmp(status, "nao_reconhecido") == 0) {

            // lcd.clear();
            // lcd.setCursor(0, 0);
            // lcd.print("Acesso Negado");
            // delay(2000);
            // lcd.clear();
            // lcd.setCursor(0, 0);
            // lcd.print("Esperando cmd...");
          }
        }

 
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
