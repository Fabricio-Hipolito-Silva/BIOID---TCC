#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WebSocketsClient.h>
#include "fingerprint_init.h"
#include "secret.h"
#include "validar.h"
#include <LiquidCrystal_I2C.h>

int ValidarID();

void validarSetup() {
    Serial.begin(9600);
    inicializarTelaLCD();
    inicializarTecladoMatriz();
    inicializarSensor();
    conectarWifi();
    inicializarWebSocket();
}

void validarLoop(){
    webSocket.loop();
    
    int idDigital = ValidarID();
    String NomeDigital = ValidarNome(idDigital);
    if (idDigital >= 0) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ID:");
        lcd.setCursor(4,0);
        lcd.print(idDigital);
        lcd.setCursor(0,1);
        lcd.print(NomeDigital);
        delay(5000);
    } else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ID não reconhecida.");
        delay(5000);
    }
    if (idDigital >= 0) {
        HTTPClient post;
        String url = "http://" + String(Server) + "/ETEC/3MIN/TCC/BIOID%20_%20TCC/api/salvar_ultimo_usuario.php";
        String dados = "id=" + String(idDigital);
        post.begin(url);
        post.addHeader("Content-Type", "application/x-www-form-urlencoded");
        post.POST(dados);
        post.end();
    }
    }

