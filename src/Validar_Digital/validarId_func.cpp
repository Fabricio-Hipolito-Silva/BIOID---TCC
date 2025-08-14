#include "validar.h"
#include "secret.h"
#include "fingerprint_init.h"



int ValidarID() {
    int p;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Coloque o dedo");
    lcd.setCursor(0,1);
    lcd.print("no sensor...");
    while ((p = finger.getImage()) != FINGERPRINT_OK);

    if (finger.image2Tz(1) != FINGERPRINT_OK) return -1;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Imagem Capturada");
    lcd.setCursor(0,1);
    lcd.print("Retire o Dedo");
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
    http.begin("http://" + String(Server) + "/ETEC/3MIN/TCC/BIOID%20_%20TCC/api/consultar.php?id="+ String(idV));
    int resposta = http.GET();
    if (resposta > 0){
       String nome = http.getString();
       http.end();
       return nome;
    }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Erro na Consulta");
        lcd.setCursor(0,1);
        lcd.print("do Nome");
        http.end(); 
        return "";  
    };
    
    
};
