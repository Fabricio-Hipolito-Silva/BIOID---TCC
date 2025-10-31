#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include <Adafruit_Fingerprint.h>
#include <ArduinoJson.h>
#include <Keypad.h>
#include <WebSocketsClient.h>
#include "bioID_init.h"

bool verificacaoAtiva = false;
int etapaVerificacao = 0; // controla o passo atual da verificação

void iniciarVerificacao() {
  verificacaoAtiva = true;
  etapaVerificacao = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Modo Verificacao");
  delay(1000);
  lcd.clear();
  lcd.print("Aguardando dedo");
  lcd.setCursor(0, 1);
  lcd.print("...");
}

void pararVerificacao() {
  verificacaoAtiva = false;
  etapaVerificacao = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Esperando cmd...");
}

void verificarTeclado(){
 char tecla = teclado->getKey();
 if(!tecla){
    return;
 };
 if(tecla == '*'){
    modoDigitacaoRM = true;
    rmDigitado = "";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Digite o RM:");
    return;
 };
 if(modoDigitacaoRM == true){
    if (tecla >= '0' && tecla <= '9') {
      rmDigitado += tecla;
      lcd.setCursor(0, 1);
      lcd.print(rmDigitado);
 }else if(tecla == '#'){
      StaticJsonDocument<200> doc;
      doc["action"] = "rm_digitado";
      doc["rm"] = rmDigitado.toInt();
      String json;
      serializeJson(doc, json);
      webSocket.sendTXT(json);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("RM Enviado");
      delay(1000);
    };
 };


}
// Função que executa 1 "passo" da verificação por vez
void verificarDigitalStep() {
  static unsigned long ultimoTempo = 0;
  if (!verificacaoAtiva) return;

  // não executa rápido demais
  if (millis() - ultimoTempo < 100) return;
  ultimoTempo = millis();

  int result;

  switch (etapaVerificacao) {

    case 0: // espera dedo
      result = finger.getImage();
      if (result == FINGERPRINT_NOFINGER) return;
      if (result != FINGERPRINT_OK) {
        lcd.clear();
        lcd.print("Erro leitura");
        etapaVerificacao = 0;
        delay(500);
        return;
      }
      etapaVerificacao = 1;
      break;

    case 1: // converte
      if (finger.image2Tz(1) != FINGERPRINT_OK) {
        lcd.clear();
        lcd.print("Erro converter");
        etapaVerificacao = 0;
        delay(500);
        return;
      }
      etapaVerificacao = 2;
      break;

    case 2: // busca no banco
      {
        int search = finger.fingerSearch();
        if (search == FINGERPRINT_OK) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Digital OK!");
          lcd.setCursor(0, 1);
          lcd.print("Slot: ");
          lcd.print(finger.fingerID);

          StaticJsonDocument<200> doc;
          doc["acao"] = "verificacao_ok";
          doc["slot"] = finger.fingerID;
          String json;
          serializeJson(doc, json);
          webSocket.sendTXT(json);

          delay(1500);
        } else {
          lcd.clear();
          lcd.print("Nao encontrada");
          delay(1000);
        }
        lcd.clear();
        lcd.print("Retire o dedo");
        etapaVerificacao = 3;
      }
      break;

    case 3: // espera retirar dedo
      if (finger.getImage() == FINGERPRINT_NOFINGER) {
        lcd.clear();
        lcd.print("Aguardando dedo");
        lcd.setCursor(0, 1);
        lcd.print("...");
        etapaVerificacao = 0;
      }
      break;
  }
}