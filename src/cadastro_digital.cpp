#include "LiquidCrystal_I2C.h"
#include <Adafruit_Fingerprint.h>
#include <ArduinoJson.h>
#include "bioID_init.h"
#include "base64.h"


bool cadastrarDigital(int rm, int slot){
    // Verifica se o slot está ocupado
    uint8_t p = finger.loadModel(slot);
    if (p == FINGERPRINT_OK) {
        lcd.clear();
        lcd.print("Slot ocupado!");
        delay(2000);
        return false;
    }

    // Início do cadastro normal
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Coloque o dedo");
    lcd.setCursor(0, 1);
    lcd.print("no sensor...");
    while (finger.getImage() != FINGERPRINT_OK);

    if(finger.image2Tz(1) != FINGERPRINT_OK) return false;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remova o dedo");
    delay(2000);
    while(finger.getImage() == FINGERPRINT_OK);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Coloque o mesmo");
    lcd.setCursor(0, 1);
    lcd.print("dedo novamente..");
    while (finger.getImage() != FINGERPRINT_OK);
    
    if(finger.image2Tz(2) != FINGERPRINT_OK) return false;
    if(finger.createModel() != FINGERPRINT_OK) return false;

    if(finger.storeModel(slot) != FINGERPRINT_OK) return false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Digital Cadastrada!");
    delay(2000);

    // Envia JSON para o WebSocket
    StaticJsonDocument<800> doc;
    doc["acao"] = "digital_cadastrada";
    doc["rm"] = rm;
    doc["slot"] = slot;
    String jsonString;
    serializeJson(doc, jsonString);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enviando...");
    delay(1000);
    webSocket.sendTXT(jsonString);

    return true;
}
