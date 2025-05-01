#include "cadastro.h"

bool cadastroDedo() {
    int p;
  
    // Primeira imagem
    while ((p = finger.getImage()) != FINGERPRINT_OK);
    if (finger.image2Tz(1) != FINGERPRINT_OK) return false;
    Serial.println("Primeira imagem capturada. Retire o dedo...");
  
    delay(2000);
    while (finger.getImage() != FINGERPRINT_NOFINGER);
  
    // Segunda imagem
    Serial.println("Coloque o mesmo dedo novamente...");
    while ((p = finger.getImage()) != FINGERPRINT_OK);
    if (finger.image2Tz(2) != FINGERPRINT_OK) return false;
  
    // Criação do modelo
    p = finger.createModel();
    if (p == FINGERPRINT_OK) {
      Serial.println("Digitais coincidem. Salvando...");
    } else if (p == FINGERPRINT_ENROLLMISMATCH) {
      Serial.println("Digitais não combinam. Tente novamente.");
      return false;
    } else {
      Serial.println("Erro ao criar modelo.");
      return false;
    }
  
    // Armazenamento
    if (finger.storeModel(id) == FINGERPRINT_OK) {
      Serial.print("Digital cadastrada com sucesso no slot ");
      Serial.println(id);
      return true;
    } else {
      Serial.println("Erro ao salvar digital.");
      return false;
    }
  }
  