#include "display.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "key.h"
#include "serial.h"
#include <string.h>
#include "control.h"
#include "buzzer.h"
#include "pinAccess.h"
#include <stdbool.h>
#include "timeDate.h"
#include "ldr.h"
#include "rele/rele.h"

#define MAX_COMBINATION_SIZE 4

// Variables globales
char combination[MAX_COMBINATION_SIZE + 1] = {'4', '5', '7', '2', '\0'};
char master_combination[MAX_COMBINATION_SIZE + 1] = {'*', '5', '8', '#', '\0'};
char input_combination[MAX_COMBINATION_SIZE + 1] = {0}; // Inicializar en 0 para evitar basura
int tryNumber = 0; // Contador de intentos

static int numberOfCodeChars = 0;
static int numberOfHashKeyReleased = 0; // Contador de la tecla '#'
bool incorrectCodeState = false; // Estado de código incorrecto
static bool anyKey = false;

// Variables de estado
static bool awaitingInput = false;  // Controla si estamos esperando la entrada
static bool changingCombination = false;  // Estado para cambiar la clave
static bool showClock = true; // Para controlar si se debe mostrar la hora
static bool settingTime = false;


//variables para cambiar la hora
static bool settingHour = true;    // Indica si estamos configurando la hora
static bool minuteEntered = false; // Indica si los minutos han sido ingresados
static int timeData[4] = {0};      // Almacena hora y minutos
static int timeIndex = 0;          // Índice para los datos de tiempo (hora y minutos)

// Getters y setters para acceder a las variables de estado desde otras librerías
bool isAwaitingInput() {
    return awaitingInput;
}

void setAwaitingInput(bool value) {
    awaitingInput = value;
}

bool isChangingCombination() {
    return changingCombination;
}

void setChangingCombination(bool value) {
    changingCombination = value;
}

bool getIncorrectCodeState() {
    return incorrectCodeState;
}

int getTryNumber() {
    return tryNumber;
}

int getNumberOfChars(){
    return numberOfCodeChars;
}

void setClockShow(bool show){
    showClock = show;
}

bool getClockShow() {
    return showClock;
}

void setTime(bool set){
    settingTime = set;
}

bool getSetTime(){
    return settingTime;
}

bool getPressedKey(){
    return anyKey;
}

// Máquina de estados para manejar entradas
typedef enum {
    STATE_IDLE,           // Estado en espera de una acción
    STATE_AWAITING_INPUT, // Estado de ingreso de clave
    STATE_CHANGE_COMBINATION, // Estado de cambio de combinación
    STATE_SETTING_TIME // Estado para setear la hora
} systemState_t;

systemState_t currentState = STATE_IDLE;


void comparedKey() {
    char keyPressed = KeyUpdate();

    if (keyPressed == '\0') {
        anyKey = false; // No hay tecla presionada
        return;
    } else {
        anyKey = true; // Hay una tecla presionada
    }

    if (keyPressed == 'B') {
        setBuzzerState(true);
        setBuzzerTimeOn(200);
        if (!getSystemState()) {
            currentState = STATE_IDLE;
        } else {
            return;
        }
    }

    switch (currentState) {
        case STATE_IDLE:
            setChangingCombination(false);
            setAwaitingInput(false);
            incorrectCodeState = false;
            setClockShow(true);

            if (keyPressed == '#') {
                numberOfHashKeyReleased++;
                if (numberOfHashKeyReleased >= 2) {
                    numberOfHashKeyReleased = 0;
                    numberOfCodeChars = 0;
                    incorrectCodeState = false;
                    tryNumber = 0;
                    setAwaitingInput(false);
                    setChangingCombination(false);
                    memset(input_combination, 0, sizeof(input_combination));
                    serial_print("\nReiniciando intentos y secuencia de código.\n");
                    setClockShow(true);
                }
                return;
            }

            if (keyPressed == 'D') {
                setAwaitingInput(true);
                currentState = STATE_AWAITING_INPUT;
                numberOfCodeChars = 0;
                memset(input_combination, 0, sizeof(input_combination));
                serial_print("Ingrese la clave (4 dígitos): ");
                showClock = false;  // Desactivar la visualización de la hora

            } else if (keyPressed == 'C') {
                if (!getSystemState()) {
                    setChangingCombination(true);
                    setClockShow(false);
                    currentState = STATE_CHANGE_COMBINATION;
                    numberOfCodeChars = 0;
                    memset(input_combination, 0, sizeof(input_combination));
                    serial_print("Ingrese la nueva clave (4 dígitos): ");
                } else {
                    serial_print("No se puede cambiar la clave mientras el sistema está bloqueado.\n");
                }

            } else if (keyPressed == 'A') {
                if (!getSetTime()) {
                    setTime(true);
                    currentState = STATE_SETTING_TIME;  // Cambiar el estado para setear la hora
                    serial_print("Iniciando configuración de hora.\n");
                    showClock = false;  // Desactivar la visualización de la hora durante la configuración
                }
            }

            break;

        case STATE_AWAITING_INPUT:
            if (numberOfCodeChars < MAX_COMBINATION_SIZE) {
                input_combination[numberOfCodeChars++] = keyPressed;
                serial_print(&keyPressed);
                displayCharPositionWrite(numberOfCodeChars + 4, 1);
                displayStringWrite("*");

                if (numberOfCodeChars == MAX_COMBINATION_SIZE) {
                    input_combination[numberOfCodeChars] = '\0';
                    setAwaitingInput(false);
                    currentState = STATE_IDLE;
                    incorrectCodeState = false;
                    serial_print("\n");

                    // Verificar si la combinación ingresada es correcta o es la combinación maestra
                    if (strcmp(combination, input_combination) == 0 || strcmp(master_combination, input_combination) == 0) {
                        if (getSystemState()) {
                            showClock = true;
                            serial_print("¡Combinación correcta! Sistema desbloqueado.\n");
                            setSystemState(false);
                            setReleLockState(true);

                        } else {
                            showClock = true;
                            serial_print("¡Combinación correcta! Sistema bloqueado.\n");
                            setSystemState(true);
                            setReleLockState(false);
                        }
                        setBuzzerState(true);
                        setBuzzerTimeOn(300);
                        tryNumber = 0;
                    } else {
                        tryNumber++;
                        incorrectCodeState = true;
                        if (tryNumber >= 3) {
                            serial_print("¡Sistema bloqueado por demasiados intentos fallidos!\n");
                            setBuzzerState(true);
                            setBuzzerTimeOn(600);
                            setReleLockState(false);
                        } else {
                            setBuzzerState(true);
                            setBuzzerTimeOn(600);
                            setReleLockState(false);
                            serial_print("Combinación incorrecta.\nIntentos restantes: ");
                            char try_left[2];
                            snprintf(try_left, sizeof(try_left), "%d", 3 - tryNumber);
                            serial_print(try_left);
                        }
                    }
                    memset(input_combination, 0, sizeof(input_combination));
                }
            }
            break;
        case STATE_CHANGE_COMBINATION:
            if (numberOfCodeChars < MAX_COMBINATION_SIZE) {
                input_combination[numberOfCodeChars++] = keyPressed;

                serial_print(&keyPressed);
                displayCharPositionWrite(numberOfCodeChars+4, 1);
                displayStringWrite("*"); 
                if (numberOfCodeChars == MAX_COMBINATION_SIZE) {
                    input_combination[numberOfCodeChars] = '\0';
                    setChangingCombination(false);
                    setAwaitingInput(false);
                    incorrectCodeState = false;
                    setSystemState(true);
                    setClockShow(true);
                    currentState = STATE_IDLE;
                    strcpy(combination, input_combination);
                    serial_print("\n¡Clave cambiada exitosamente!\n");
                    setBuzzerState(true);
                    setBuzzerTimeOn(300);
                    memset(input_combination, 0, sizeof(input_combination));

                }

            }
            break;
        case STATE_SETTING_TIME:
            if (getSetTime()) {
                static bool settingHour = true;    // Indica si estamos configurando la hora
                static bool hourEntered = false;   // Indica si la hora ha sido ingresada
                static bool minuteEntered = false; // Indica si los minutos han sido ingresados
                static int timeData[4] = {0};      // Almacena hora y minutos
                static int timeIndex = 0;          // Índice para los datos de tiempo (hora y minutos)

                if (keyPressed >= '0' && keyPressed <= '9') {
                    int value = keyPressed - '0'; // Convertir el carácter presionado a un número

                    if (settingHour && timeIndex < 2) {
                        // Ingresando hora
                        timeData[timeIndex++] = value;
                        displayCharPositionWrite(6 + timeIndex - 1, 1); // Mostrar el dígito ingresado
                        char valueStr[2];
                        snprintf(valueStr, sizeof(valueStr), "%d", value);
                        displayStringWrite(valueStr);

                    } else if (!settingHour && timeIndex < 4) {
                        // Ingresando minutos
                        timeData[timeIndex++] = value;
                        displayCharPositionWrite(0, 1);
                        displayStringWrite("Min: ");
                        displayCharPositionWrite(5 + timeIndex - 3, 1); // Mostrar el dígito ingresado
                        char valueStr[2];
                        snprintf(valueStr, sizeof(valueStr), "%d", value);
                        displayStringWrite(valueStr);
                    }
                }

                if (keyPressed == 'A') {
                    if (settingHour) {
                        if (timeIndex < 2) {
                            // Si se presiona 'A' antes de ingresar los dos dígitos de la hora
                            serial_print("\nPor favor, ingrese los dos dígitos de la hora antes de confirmar.");
                        } else {
                            // Confirmar hora
                            settingHour = false; // Pasar a configuración de minutos
                            timeIndex = 2;       // Reiniciar el índice para los minutos

                            // Limpiar el display y mostrar el mensaje "Min:"
                            displayClear();
                            displayCharPositionWrite(0, 0);
                            displayStringWrite("Set time");
                            displayCharPositionWrite(0, 1);
                            displayStringWrite("Min: ");
                            serial_print("\nHora confirmada. Ingrese los minutos: ");
                        }
                    } else {
                        if (timeIndex < 4) {
                            // Si se presiona 'A' antes de ingresar los dos dígitos de los minutos
                            serial_print("\nPor favor, ingrese los dos dígitos de los minutos antes de confirmar.");
                        } else {
                            // Confirmar minutos y guardar configuración
                            minuteEntered = true;
                            int hours = timeData[0] * 10 + timeData[1];
                            int minutes = timeData[2] * 10 + timeData[3];
                            dateAndTimeWrite(2024, 9, 16, hours, minutes, 0); // Establecer hora y minutos
                            serial_print("\nHora y minutos configurados correctamente.\n");
                            setBuzzerState(true);
                            setBuzzerTimeOn(300);
                            settingHour = true;
                            hourEntered = false;
                            minuteEntered = false;
                            timeIndex = 0;
                            setTime(false); // Finalizar configuración de hora
                            currentState = STATE_IDLE; // Volver al estado IDLE
                            showClock = true; // Mostrar la hora

                        }
                    }
                }
            }
            break;

    }
}

