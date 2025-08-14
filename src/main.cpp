#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte LINHAS = 4;
const byte COLUNAS = 3;

char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pinosLinhas[LINHAS] = {13, 12, 14, 27};
byte pinosColunas[COLUNAS] = {26, 25, 33};

Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço 0x27, LCD 16x2

void setup() {
  Serial.begin(9600);
  Wire.begin(18, 19); // SDA = 19, SCL = 18
  lcd.init();
  lcd.backlight();
}

void loop() {
    char tecla = teclado.getKey();
    if (tecla) {
    lcd.setCursor(0,1);
    lcd.print(tecla);
  }
}