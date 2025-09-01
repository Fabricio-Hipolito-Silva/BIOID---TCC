#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WebSocketsClient.h>
#include "cadastro.h"
#include "validar.h"
#include "fingerprint_init.h"

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("WS Desconectado");
            Serial.println("WebSocket Disconnected");
            break;
        case WStype_CONNECTED:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("WS conectado");
            Serial.println("WebSocket Connected");
            webSocket.sendTXT("Hello Server");
            break;
        case WStype_TEXT:
            delay(1000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("WS Mensagem:");
            lcd.setCursor(0,1);
            lcd.print((char *)payload);
            Serial.printf("WebSocket Message: %s\n", payload);
            break;
    }
}


void setup(){
    inicializarTelaLCD();
    inicializarTecladoMatriz();
    inicializarSensor();
    conectarWifi();
    webSocket.begin(Server, 8080, "/");
    webSocket.onEvent(webSocketEvent);
}void loop(){
    webSocket.loop();
}
