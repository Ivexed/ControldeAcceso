#include "mbed.h"
#include "arm_book_lib.h"
#include <string.h>
#include "buzzer.h"
#include "control.h"

DigitalOut buzzer(D12); // salida digital para activar la base del transistor que controla el buzzer

int     buzzerAccumulatedTime = 0;
static bool buzzerState;
static int buzzerTimeOn;

void buzzerInit(){
    buzzer = OFF;
    buzzerState = OFF;
}

void setBuzzerState(bool state) {
    buzzerState = state;
}

void setBuzzerTimeOn(int time) {
    buzzerTimeOn = time;
}


void buzzerTask() { 
    if (buzzerState) {
        buzzer = ON;
        buzzerAccumulatedTime += SYSTEM_TIME_INCREMENT_MS; // Incrementa el tiempo acumulado
        if (buzzerAccumulatedTime >= buzzerTimeOn) {
            buzzer = OFF;
            buzzerAccumulatedTime = 0; // Resetea el tiempo acumulado
            setBuzzerState(false); // Apaga el buzzer
        }
    } else {
        buzzer = OFF; // Asegura que el buzzer esté apagado cuando el estado es falso
    }
}

