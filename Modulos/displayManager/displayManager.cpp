#include "mbed.h"
#include "arm_book_lib.h"
#include "control.h"
#include "buzzer.h"
#include "key.h"
#include "ldr.h"
#include "pinAccess.h"
#include "serial.h"
#include "display.h"
#include "displayManager.h"
#include "timeDate.h"

// Definiciones y variables globales
#define MAX_COMBINATION_SIZE 4
#define DISPLAY_RS_INSTRUCTION 0
#define DISPLAY_RS_DATA 1

// Definición de los estados de la máquina de estados del display
typedef enum {
    DISPLAY_STATE_IDLE,
    DISPLAY_STATE_SHOW_SYSTEM,
    DISPLAY_STATE_SHOW_ATTEMPTS,
    DISPLAY_STATE_SHOW_COMBINATION,
    DISPLAY_STATE_SHOW_CHANGING,
    DISPLAY_SET_TIME
} displayState_t;

displayState_t currentDisplayState = DISPLAY_STATE_IDLE;
bool needsUpdate = true;


// Función para inicializar el display
void interfaceDisplayInit() {
    displayInit(DISPLAY_TYPE_LCD_HD44780, DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER);

}

// Función para actualizar el display según el estado
void interfaceDisplayUpdate() {

    displayRealTimeClock();

    if (!needsUpdate) {
        return;
    }

    switch (currentDisplayState) {
        case DISPLAY_STATE_IDLE:
            break;
          
        case DISPLAY_STATE_SHOW_SYSTEM:
            displayClear();
            showSystemState(getSystemState());
            break;

        case DISPLAY_STATE_SHOW_ATTEMPTS:
            displayClear();
            showAttemptsLeft(3 - getTryNumber());
            break;

        case DISPLAY_STATE_SHOW_COMBINATION:
            displayClear();
            showPinIntroduction();
            break;

        case DISPLAY_STATE_SHOW_CHANGING:
            displayClear();
            showChangingCombination();
            break;

        case DISPLAY_SET_TIME:
            displayClear();
            showSetTime();
            break;
    }

    needsUpdate = false;
}

// Actualizar el estado del display
void updateDisplayState(displayState_t newState) {
    if (currentDisplayState != newState) {
        currentDisplayState = newState;
        needsUpdate = true;
    }
}

// Comprobar las condiciones para cambiar el estado del display
void checkDisplayConditions() {
    backlight();
    showLdrState(getLampState());
    if (isChangingCombination()) {
        updateDisplayState(DISPLAY_STATE_SHOW_CHANGING);
    } else if (isAwaitingInput()) {
        updateDisplayState(DISPLAY_STATE_SHOW_COMBINATION);
    } else if (getIncorrectCodeState()) {
        updateDisplayState(DISPLAY_STATE_SHOW_ATTEMPTS);
    } else if (getSetTime()) {
        updateDisplayState(DISPLAY_SET_TIME);
    }else{
        updateDisplayState(DISPLAY_STATE_SHOW_SYSTEM);
    }

}



// Funciones auxiliares para mostrar diferentes mensajes en el display
void showPinIntroduction() {
    displayCharPositionWrite(0, 0);
    displayStringWrite("Ingresa PIN:");
}

void showSystemState(bool systemState) {
    displayCharPositionWrite(0, 0);
    if (systemState) {
        displayStringWrite("Sys locked");
    } else {
        displayStringWrite("Sys Unlocked");
    }

}

void showAttemptsLeft(int attemptsLeft) {
    displayCharPositionWrite(0, 1);
    char attemptsStr[16];
    if (attemptsLeft > 0) {
        snprintf(attemptsStr, sizeof(attemptsStr), "Intentos: %d", attemptsLeft);
        displayStringWrite(attemptsStr);
    } else {
        displayClear();
        displayCharPositionWrite(0, 1);
        displayStringWrite("BLOCKED");
    }
}

void showChangingCombination() {
    displayCharPositionWrite(0, 0);
    displayStringWrite("Ingr. nuevo PIN");
}

void showSetTime() {
    displayCharPositionWrite(0, 0);
    displayStringWrite("Set time");  // Mostrar mensaje de configuración de hora
    displayCharPositionWrite(0, 1);
    displayStringWrite("Hour: ");
}

// Mostrar la hora en tiempo real en el display
void displayRealTimeClock() {
    if (!getClockShow()) return;  // No mostrar la hora si `showClock` es false

    time_t currentTime = time(NULL);  // Obtener el tiempo actual en segundos
    static time_t lastUpdateTime = 0; // Última vez que se actualizó el reloj

    if (currentTime != lastUpdateTime) {
        lastUpdateTime = currentTime; // Actualizar la referencia de tiempo

        struct tm *localTime = localtime(&currentTime);  // Convertir el tiempo a formato legible
        char timeStr[16];
        snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", 
                 localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

        displayCharPositionWrite(0, 1);  // Ubicar el cursor
        displayStringWrite(timeStr);     // Escribir la hora
    }
}

// Función para manejar el backlight del display
void backlight() {
    static int timeOnBacklight = 0;
    static bool backlightState = false;

    // Si se presiona una tecla, reiniciar el contador y encender el backlight
    if (getPressedKey()) {
        timeOnBacklight = 0;  // Reiniciar el tiempo al presionar una tecla
        backlightOn();
    } else {
        backlightState = true;
    }

    // Mantener el backlight encendido mientras no haya pasado el tiempo límite
    if (timeOnBacklight < REFRESH_TIME_BACKLIGHT) {
        backlightOn();
        timeOnBacklight += SYSTEM_TIME_INCREMENT_MS;  // Incrementar el tiempo
        backlightState = true;
    } else if (backlightState) {
        backlightOff();  // Apagar el backlight cuando el tiempo se exceda
        backlightState = false;
    }
}


void showLdrState(bool state) {
    if(isStateChanged()){
        if (state) {
            displayCharPositionWrite(11, 1);
            displayStringWrite("Night");
        } else {
            displayCharPositionWrite(11, 1);
            displayStringWrite("Day  ");
        }
    }
}