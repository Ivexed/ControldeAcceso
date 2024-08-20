#include "mbed.h"
#include "arm_book_lib.h"
#include "key.h"
#include "serial.h"
#include <string.h>
#include "control.h"
#include "buzzer.h"
#include "pinAccess.h"


char    combination[MAX_COMBINATION_SIZE + 1]; // Añadimos un espacio adicional para el caracter nulo
char    input_combination[MAX_COMBINATION_SIZE + 1]; // Añadimos un espacio adicional para el caracter nulo
int     tryNumber = 0; // variable para contar el número de intentos


void passSet() {
    static bool clavePin = false;
    if (!clavePin) {
        serial_print("Ingrese la combinación de botones (usando 1, 2, 3, 4):\n");
        keypadTask(combination);
        clavePin = true;
        setBuzzerState(true);
        setBuzzerTimeOn(100);  // Configuración del tiempo del buzzer a 100 ms
        serial_print("\nCombinación almacenada: ");
        serial_print(combination);
        serial_print("\n");
    }
}

void keypadTask(char* comb) {
    int i = 0;
    char key;
    while (i < MAX_COMBINATION_SIZE) {
        key =  KeyUpdate();  // Llama a la función que maneja el teclado matricial
        if (key != '\0') {  // Si se presionó una tecla
            comb[i++] = key;
            serial_print(&key);  // Imprime la tecla presionada
        }
        thread_sleep_for(SYSTEM_TIME_INCREMENT_MS); // Tiempo del ciclo principal, ajustado con la misma base de tiempo que `KeyUpdate`
    }
    comb[i] = '\0'; // Termina la cadena con un caracter nulo
}

void comparedKey() {
    char keyPressed =  KeyUpdate();

    if (keyPressed == 'D') {
        if (getSystemState()) {
            serial_print("Ingrese la clave para desbloquear.\n");
        } else {
            serial_print("Ingrese la clave para bloquear.\n");
        }

        keypadTask(input_combination);

        if (strcmp(combination, input_combination) == 0) {
            if (getSystemState()) {
                serial_print("¡Combinación correcta! Sistema desbloqueado.\n");
                setSystemState(false);
                setBuzzerState(true);
                setBuzzerTimeOn(300);    // Configuración del tiempo del buzzer
            } else {
                serial_print("¡Combinación correcta! Sistema bloqueado.\n");
                setSystemState(true);
                setBuzzerState(true);
                setBuzzerTimeOn(300);  // Configuración del tiempo del buzzer
            }
            tryNumber = 0; // Resetear el contador de intentos fallidos
        } else {
            tryNumber++;
            if (tryNumber >= 3) {
                serial_print("¡Sistema bloqueado por demasiados intentos fallidos!\n");
                setBuzzerState(true);
                setBuzzerTimeOn(600);  // Configuración del tiempo del buzzer
            } else {
                setBuzzerState(true);
                setBuzzerTimeOn(600); // Configuración del tiempo del buzzer
                serial_print("Combinación incorrecta: ");
                serial_print(input_combination);
                serial_print("\nIntentos restantes: ");
                char try_left = '0' + (3 - tryNumber);
                serial_print(&try_left);
                serial_print("\n");
            }
        }
    }

}

