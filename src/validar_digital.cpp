#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include <Adafruit_Fingerprint.h>
#include <ArduinoJson.h>
#include "bioID_init.h"

bool verificacaoAtiva = false;  // controle externo

void iniciarVerificacao() {
    verificacaoAtiva = true;
}

void pararVerificacao() {
    verificacaoAtiva = false;
}

void validarDigital() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Modo Verificacao");
    delay(1000);

    lcd.clear();
    lcd.print("Aguardando dedo");
    lcd.setCursor(0, 1);
    lcd.print("...");

    while (verificacaoAtiva) {
        int result = finger.getImage();
        if (result == FINGERPRINT_NOFINGER) {
            delay(100);
            continue; // continua esperando dedo
        }

        if (result != FINGERPRINT_OK) {
            lcd.clear();
            lcd.print("Erro leitura");
            delay(1000);
            continue;
        }

        // Converte imagem
        if (finger.image2Tz(1) != FINGERPRINT_OK) {
            lcd.clear();
            lcd.print("Erro converter");
            delay(1000);
            continue;
        }

        // Procura no banco
        int search = finger.fingerSearch();
        if (search == FINGERPRINT_OK) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Digital OK!");
            lcd.setCursor(0, 1);
            lcd.print("Slot: ");
            lcd.print(finger.fingerID);

            // Envia via WebSocket
            StaticJsonDocument<200> doc;
            doc["acao"] = "verificacao_ok";
            doc["slot"] = finger.fingerID;
            String json;
            serializeJson(doc, json);
            webSocket.sendTXT(json);

            delay(2000);
        } else {
            lcd.clear();
            lcd.print("Nao encontrada");
            delay(1500);
        }

        // Espera tirar o dedo antes da próxima leitura
        lcd.clear();
        lcd.print("Retire o dedo");
        while (finger.getImage() != FINGERPRINT_NOFINGER) delay(50);

        lcd.clear();
        lcd.print("Aguardando dedo");
        lcd.setCursor(0, 1);
        lcd.print("...");
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Verificacao");
    lcd.setCursor(0, 1);
    lcd.print("Encerrada");
}
