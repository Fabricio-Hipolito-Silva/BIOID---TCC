#include "LiquidCrystal_I2C.h"
#include <Adafruit_Fingerprint.h>
#include "bioID_init.h"
#include "base64.h"

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
    if(finger.getModel() != FINGERPRINT_OK) return false; // Check if model exists
    uint8_t bytesReceived[512]; // template real tem 512 bytes
    uint16_t index = 0;
    while (index < 512) {
    if (mySerial.available()) {
      bytesReceived[index++] = mySerial.read();
    }
  }if (index != 512) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Erro ao ler");
        lcd.setCursor(0, 1);
        lcd.print("template!");
        delay(2000);
        return false;
    }
    String encoded = base64::encode(bytesReceived, 512);
    Serial.println("Template em Base64:");
    Serial.println(encoded);
    return true;


    

//!!IREI TER QUE MODIFICAR A BIBLIOTECA

};