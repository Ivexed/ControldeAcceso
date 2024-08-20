#include "mbed.h"
#include "arm_book_lib.h"
#include <string.h>

#define LDR_LEVEL            0.5    // Valor de referencia para el nivel del LDR
#define LDR_THRESHOLD_ON     0.4    // Umbral para encender la lámpara
#define LDR_THRESHOLD_OFF    0.6    // Umbral para apagar la lámpara

DigitalOut lamp(D2); // salida digital para activar la lampara
AnalogIn LDR(A0); // Definimos la entrada analógica del LDR

float   LDR_value; // variable para almacenar el valor del LDR

void ldrInit() {
    lamp = OFF;
}

void ldrTask() {
    LDR_value = LDR.read(); // Lee el valor analógico del LDR
    if (LDR_value > LDR_THRESHOLD_OFF) {
        lamp = OFF;  // Apagar el foco si el valor del LDR es mayor que el umbral de apagado
    } else if (LDR_value < LDR_THRESHOLD_ON) {
        lamp = ON;  // Encender el foco si el valor del LDR es menor que el umbral de encendido
    }
}
