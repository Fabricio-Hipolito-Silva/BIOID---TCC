#include "validar.h"
#include "secret.h"
#define LED_AMARELO 33
#define LED_VERDE 32
#define LED_VERMELHO 25



int ValidarID() {
    int p;
   
    Serial.println("Coloque o dedo no sensor...");
    while ((p = finger.getImage()) != FINGERPRINT_OK);

    if (finger.image2Tz(1) != FINGERPRINT_OK) return -1;

    Serial.println("Imagem capturada. Retire o Dedo");
    digitalWrite(LED_AMARELO, LOW);
    delay(1000);

    while (finger.getImage() != FINGERPRINT_NOFINGER);
    digitalWrite(LED_AMARELO, HIGH);

    p = finger.fingerSearch();
    if (p == FINGERPRINT_OK) {
        int idV = finger.fingerID;
        return idV;
    } else {
        return -1;
    }
};

String ValidarNome(int idV) {
    HTTPClient http;
    http.begin("http://" + String(Server) + "/BIOID%20_%20TCC/api/consultar.php?id="+ String(idV));
    int resposta = http.GET();
    if (resposta > 0){
       String nome = http.getString();
       http.end();
       return nome;
    }else{
        Serial.print("Erro na consulta do Nome");
        http.end(); 
        return "";  
    };
    
    
};
