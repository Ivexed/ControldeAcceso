#include "control.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include <string.h>
#include "display.h"
#include "ldr.h"

#define LDR_LEVEL            0.5    // Valor de referencia para el nivel del LDR
#define LDR_THRESHOLD_ON     0.4    // Umbral para encender la lámpara
#define LDR_THRESHOLD_OFF    0.6    // Umbral para apagar la lámpara


DigitalOut lamp(D2); // salida digital para activar rele de lampara
AnalogIn LDR(A0);    // Definimos la entrada analógica del LDR

static bool lampState; 
static bool ldrChanged = false;  // Variable global para verificar si el LDR cambió

float LDR_value; // Variable para almacenar el valor del LDR

// Inicialización de la lámpara
void ldrInit() {
    lamp = OFF;
    setLampState(false);
    setChanged(true);
}

// Retorna el estado actual de la lámpara

void setLampState(bool lampst){
    lampState = lampst;
}
bool getLampState() {
    return lampState;
}

void setChanged(bool change){
    ldrChanged = change;
}
bool isStateChanged() {
    return ldrChanged;
}


void ldrTask() {
    LDR_value = LDR.read();  // Leer el valor del LDR actual
    static bool lampb = true;  // Estado previo de la lámpara

    // Mantener la lógica de control de la lámpara
    if(LDR_value > LDR_THRESHOLD_OFF) {
        lamp = OFF;
        setLampState(false);  // Actualizar el estado de la lámpara en la variable global
    } else if (LDR_value < LDR_THRESHOLD_ON) {
        lamp = ON;
        setLampState(true);   // Actualizar el estado de la lámpara en la variable global
    }

    // Comparar el estado actual de la lámpara con el anterior para detectar un cambio
    if (getLampState() != lampb) {
        setChanged(true);  // Indicar que ha habido un cambio de estado
        lampb = getLampState();  // Actualizar el estado previo de la lámpara
    } else {
        setChanged(false);  // No hubo cambio, mantener el flag en false
    }
}

