#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include "fingerprint_init.h"
#include "secret.h"
#include "validar.h"
#define LED_AMARELO 33
#define LED_VERDE 32
#define LED_VERMELHO 25


int ValidarID();

void validarSetup() {
    Serial.begin(9600);
    inicializarSensor();
    conectarWifi();
}

void validarLoop(){
    
    int idDigital = ValidarID();
    String NomeDigital = ValidarNome(idDigital);
    if (idDigital >= 0) {
        Serial.print("ID validada com sucesso: ");
        Serial.println(idDigital);
        Serial.print("E de nome ");
        Serial.print(NomeDigital);
        digitalWrite(LED_VERDE, HIGH);
        digitalWrite(LED_AMARELO, LOW);
        delay(5000);
        digitalWrite(LED_VERDE, LOW);
        digitalWrite(LED_AMARELO, HIGH);
    } else {
        Serial.println("ID não reconhecida.");
        digitalWrite(LED_VERMELHO, HIGH);
        digitalWrite(LED_AMARELO, LOW);
        delay(5000);
        digitalWrite(LED_VERMELHO, LOW);
        digitalWrite(LED_AMARELO, HIGH);
    }
    if (idDigital >= 0) {
        HTTPClient post;
        String url = "http://" + String(Server) + "/BIOID%20_%20TCC/api/salvar_ultimo_usuario.php";
        String dados = "id=" + String(idDigital);
        post.begin(url);
        post.addHeader("Content-Type", "application/x-www-form-urlencoded");
        post.POST(dados);
        post.end();
    }
    }

