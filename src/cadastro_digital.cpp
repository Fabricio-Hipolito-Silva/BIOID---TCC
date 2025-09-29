#include "LiquidCrystal_I2C.h"
#include <Adafruit_Fingerprint.h>
#include <ArduinoJson.h>
#include "bioID_init.h"
#include "base64.h"

int encontrarSlot() {
  for (int id = 1; id < 127; id++) { // depende da capacidade do sensor
    uint8_t p = finger.loadModel(id);
    if (p != FINGERPRINT_OK) {
      return id;  // achou slot vazio
    }
  }
  return -1; // sensor cheio
}


bool cadastrarDigital(int rm){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Coloque o dedo");
    lcd.setCursor(0, 1);
    lcd.print("no sensor...");
    while (finger.getImage() != FINGERPRINT_OK); // Wait for finger to be placed
    if(finger.image2Tz(1) != FINGERPRINT_OK) return false; // Convert image to template
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remova o dedo");
    delay(2000); // Wait for finger to be removed
    while(finger.getImage() == FINGERPRINT_OK); // Wait for finger to be removed
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Coloque o mesmo");
    lcd.setCursor(0, 1);
    lcd.print("dedo novamente..");
    while (finger.getImage() != FINGERPRINT_OK); // Wait for finger to be placed again
    if(finger.image2Tz(2) != FINGERPRINT_OK) return false;
    if(finger.createModel() != FINGERPRINT_OK) return false; // Create model

    int slot = encontrarSlot();
    if (slot == -1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sensor cheio!");
        delay(2000);
        return false; // Sensor cheio
    }
    if(finger.storeModel(slot) != FINGERPRINT_OK) return false; // Store model in found slot
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lendo template");
    delay(500);
  //   if(finger.getModel() != FINGERPRINT_OK) return false; // Check if model exists
  //   uint8_t bytesReceived[512]; // template real tem 512 bytes
  //   uint16_t index = 0;
  //   while (index < 512) {
  //   if (mySerial.available()) {
  //     bytesReceived[index++] = mySerial.read();
  //   }
  // }if (index != 512) {
  //       lcd.clear();
  //       lcd.setCursor(0, 0);
  //       lcd.print("Erro ao ler");
  //       lcd.setCursor(0, 1);
  //       lcd.print("template!");
  //       delay(2000);
  //       return false;
  //   }
  //   String encoded = base64::encode(bytesReceived, 512);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Digital");
    lcd.setCursor(0, 1);
    lcd.print("Cadastrada!");
    delay(2000);


    // Serial.println("Template em Base64:");
    // Serial.println(encoded);

    StaticJsonDocument<800> doc;
    doc["acao"] = "digital_cadastrada";
    doc["rm"] = rm;
    doc["template"] = "blabla";
    doc["slot"] = slot;
    String jsonString;
    serializeJson(doc, jsonString);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enviando...");
    delay(1000);
    webSocket.sendTXT(jsonString);
    return true;


    


};