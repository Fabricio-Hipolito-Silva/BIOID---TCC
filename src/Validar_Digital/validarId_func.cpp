#include "validar.h"

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
        return finger.fingerID;
    } else {
        return -1;
    }
}
