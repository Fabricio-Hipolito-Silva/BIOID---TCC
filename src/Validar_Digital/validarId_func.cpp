#include "validar.h"
#include "secret.h"


int ValidarID() {
    int p;
   
    Serial.println("Coloque o dedo no sensor...");
    while ((p = finger.getImage()) != FINGERPRINT_OK);

    if (finger.image2Tz(1) != FINGERPRINT_OK) return -1;

    Serial.println("Imagem capturada. Retire o Dedo");
    delay(1000);

    while (finger.getImage() != FINGERPRINT_NOFINGER);

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
    http.begin(String(Server) + "/BIOID%20_%20TCC/api/consultar.php?id="+ String(idV));
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
