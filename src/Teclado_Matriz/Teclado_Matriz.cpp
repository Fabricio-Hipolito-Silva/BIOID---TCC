// #include <Keypad.h>

// const byte LINHAS = 4;
// const byte COLUNAS = 3;

// char teclas[LINHAS][COLUNAS] = {
//   {'1', '2', '3'},
//   {'4', '5', '6'},
//   {'7', '8', '9'},
//   {'*', '0', '#'}
// };

// byte pinosLinhas[LINHAS] = {13, 12, 14, 27};
// byte pinosColunas[COLUNAS] = {26, 25, 33};

// Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   char tecla = teclado.getKey();
//   if (tecla) {
//     Serial.print("Tecla pressionada: ");
//     Serial.println(tecla);
//   }
// }