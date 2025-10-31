#include "LiquidCrystal_I2C.h"
#include <Adafruit_Fingerprint.h>
#include <ArduinoJson.h>
#include "bioID_init.h"
#include "base64.h"

bool atualizarDigital(int rm, int slot) {
    // Verifica se há digital no slot
    uint8_t p = finger.loadModel(slot);
    if (p != FINGERPRINT_OK) {
        lcd.clear();
        lcd.print("Slot vazio!");
        delay(2000);
        return false;
    }

    // Início da atualização
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Atualizando");
    lcd.setCursor(0, 1);
    lcd.print("digital RM:");
    lcd.print(rm);
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Coloque o dedo");
    lcd.setCursor(0, 1);
    lcd.print("no sensor...");
    while (finger.getImage() != FINGERPRINT_OK);

    if (finger.image2Tz(1) != FINGERPRINT_OK) return false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remova o dedo");
    delay(1500);
    while (finger.getImage() == FINGERPRINT_OK);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Coloque o mesmo");
    lcd.setCursor(0, 1);
    lcd.print("dedo novamente..");
    while (finger.getImage() != FINGERPRINT_OK);

    if (finger.image2Tz(2) != FINGERPRINT_OK) return false;
    if (finger.createModel() != FINGERPRINT_OK) return false;

    // Apaga a digital antiga antes de gravar a nova
    if (finger.deleteModel(slot) != FINGERPRINT_OK) {
        lcd.clear();
        lcd.print("Erro ao limpar!");
        delay(2000);
        return false;
    }

    // Grava a nova digital no mesmo slot
    if (finger.storeModel(slot) != FINGERPRINT_OK) {
        lcd.clear();
        lcd.print("Erro ao salvar!");
        delay(2000);
        return false;
    }

    // Lê e converte a nova digital em Base64
    // lcd.clear();
    // lcd.print("Lendo template...");
    // if (finger.getModel() != FINGERPRINT_OK) return false;
    // uint8_t bytesReceived[512];
    // uint16_t index = 0;
    // while (index < 512) {
    //     if (mySerial.available()) {
    //         bytesReceived[index++] = mySerial.read();
    //     }
    // }
    // if (index != 512) {
    //     lcd.clear();
    //     lcd.print("Erro ao ler");
    //     lcd.setCursor(0, 1);
    //     lcd.print("template!");
    //     delay(2000);
    //     return false;
    // }

    // String encoded = base64::encode(bytesReceived, 512);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Digital Atualizada!");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Esperando cmd...");

    // Envia JSON pelo WebSocket
    StaticJsonDocument<800> doc;
    doc["action"] = "digital_atualizada";
    doc["status"] = "sucesso";
    doc["rm"] = rm;
    doc["slot"] = slot;

    String jsonString;
    serializeJson(doc, jsonString);
    webSocket.sendTXT(jsonString);

    return true;
}
