#include "cadastro.h"

    int p;
    HTTPClient http;
    bool cadastroBanco();

bool cadastroDedo() {
    // Imagens
    while ((p = finger.getImage()) != FINGERPRINT_OK);
    if (finger.image2Tz(1) != FINGERPRINT_OK) return false;
    Serial.println("Primeira imagem capturada. Retire o dedo...");
  
    delay(2000);
    while (finger.getImage() != FINGERPRINT_NOFINGER);
  
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
    if (finger.storeModel(id) == FINGERPRINT_OK && cadastroBanco()) {
      Serial.print("Digital cadastrada com sucesso no slot ");
      Serial.println(id);
      Serial.print("E de nome ");
      Serial.print(nome);
      return true;
    } else {
      Serial.println("Erro ao salvar digital.");
      return false;
    }




  }

  bool cadastroBanco(){
  //Envio para o Banco (Fazer uma função disso para ele enviar pro banco)
  http.begin("http:" + String(Server) + "/BIOID%20_%20TCC/api/cadastro.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String dados = "id=" + String(id) + "&nome=" + nome;
  int resposta = http.POST(dados);

  if(resposta > 0){
    Serial.println("Cadastrado com Sucesso no nome de " + http.getString());
    http.end();
    return true;
  }else{
    Serial.println("Erro ao cadastrar");
    http.end();
    return false;
  }
  }

  
