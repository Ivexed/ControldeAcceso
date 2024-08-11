#include "mbed.h"
#include "arm_book_lib.h"
#include <string.h>

//=====[Defines]===============================================================

#define MAX_COMBINATION_SIZE 4      // Tamaño máximo de la combinación de botones
#define TIME_INCREMENT_MS    20     //tiempo de incremento del sistema
#define TIME_DEBOUNCES_MS    120    //tiempo de antirrebote
#define TIME_MAX_BLINKING_MS 600    //tiempo para el parpadeo de led
#define LDR_LEVEL            0.5    // Valor de referencia para el nivel del LDR
#define LDR_THRESHOLD_ON     0.4    // Umbral para encender la lámpara
#define LDR_THRESHOLD_OFF    0.6    // Umbral para apagar la lámpara

//================ Object declaration ============================

DigitalOut systemLed(D4); // salida digital para el led indicador de sistema
DigitalOut lamp(D7); // salida digital para activar la lampara
DigitalOut buzzer(D8); // salida digital para activar la base del transistor que controla el buzzer

DigitalIn button1(D10); // entrada digital del boton 1
DigitalIn button2(D11); // entrada digital del boton 2
DigitalIn button3(D12); // entrada digital del boton 3
DigitalIn button4(D13); // entrada digital del boton 4
DigitalIn enterButton(BUTTON1); // Botón de Enter

AnalogIn LDR(A0); // Definimos la entrada analógica del LDR

UnbufferedSerial serial_port(USBTX, USBRX); // Definimos la UART

//=====[Declaration and initialization of public global variables]=============
bool    systemState = ON; // variable para indicar el estado del sistema ON indica en espera, OFF indica que el sistema permitió un acceso
int     tryNumber = 0; // variable para contar el número de intentos
char    combination[MAX_COMBINATION_SIZE + 1]; // Añadimos un espacio adicional para el caracter nulo
char    input_combination[MAX_COMBINATION_SIZE + 1]; // Añadimos un espacio adicional para el caracter nulo
float   LDR_value; // variable para almacenar el valor del LDR
int     acumulatedTime = 0; 
int     buzzerAccumulatedTime = 0;
static bool    buzzerState = OFF;
static int     buzzerTimeOn;

//===== Declaraciones (prototipos) de funciones ==========================
void uart_init();
void button_init();
void out_init();

void buttonTask(char* comb);
void comparedKey();
void passSet();

void serial_print(const char* str);
void ldrTask();
void buzzerTask();

//=============== Global init ======================
// Inicializo la UART
void uart_init() {
    serial_port.baud(9600);
    serial_port.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );
}

// Inicializo los botones
void button_init() {
    button1.mode(PullDown);
    button2.mode(PullDown);
    button3.mode(PullDown);
    button4.mode(PullDown);
    enterButton.mode(PullDown);
}

void out_init() {
    lamp = OFF;
    systemLed = ON;
}

//=====[Main function, the program entry point after power on or reset]========
int main() {
    uart_init();
    button_init();
    out_init();

    while (true) {
        passSet();
        comparedKey();
        ldrTask();
        buzzerTask();
        thread_sleep_for(TIME_INCREMENT_MS);
    }
}

//=====[Implementations of public functions]===================================
void serial_print(const char* str) {
    serial_port.write(str, strlen(str));
}

void buzzerTask() { 
    buzzerAccumulatedTime = buzzerAccumulatedTime + TIME_INCREMENT_MS;
    if (buzzerState) {
        buzzer = ON;
        buzzerAccumulatedTime += TIME_INCREMENT_MS;
        if (buzzerAccumulatedTime >= buzzerTimeOn) {
            buzzer = OFF;
            buzzerAccumulatedTime = 0;
            buzzerTimeOn = 0;
        }
    }
}

void buttonTask(char* comb) {
    int buttonTime = 0;  // Inicializa buttonTime
    int i = 0;
    
    while (i < MAX_COMBINATION_SIZE) {
        if (button1.read() == 1) {
            buttonTime += TIME_INCREMENT_MS;
            if (buttonTime >= TIME_DEBOUNCES_MS) {
                comb[i++] = '1';
                serial_print("1 ");
                buttonTime = 0;
            }
        } else if (button2.read() == 1) {
            buttonTime += TIME_INCREMENT_MS;
            if (buttonTime >= TIME_DEBOUNCES_MS) {
                comb[i++] = '2';
                serial_print("2 ");
                buttonTime = 0;
            }
        } else if (button3.read() == 1) {
            buttonTime += TIME_INCREMENT_MS;
            if (buttonTime >= TIME_DEBOUNCES_MS) {
                comb[i++] = '3';
                serial_print("3 ");
                buttonTime = 0;
            }
        } else if (button4.read() == 1) {
            buttonTime += TIME_INCREMENT_MS;
            if (buttonTime >= TIME_DEBOUNCES_MS) {
                comb[i++] = '4';
                serial_print("4 ");
                buttonTime = 0;
            }
        } else {
            buttonTime = 0;  // Reset buttonTime if no button is pressed
        }
        thread_sleep_for(TIME_INCREMENT_MS); // Tiempo del ciclo principal
    }
    comb[i] = '\0'; //caracter nulo
}

void passSet() {
    static bool clavePin = false;
    if (!clavePin) {
        serial_print("Ingrese la combinación de botones (usando 1, 2, 3, 4):\n");
        buttonTask(combination);
        clavePin = true;
        buzzerState = ON;
        buzzerTimeOn = 100;  // Configuración del tiempo del buzzer a 100 ms
        serial_print("\nCombinación almacenada: ");
        serial_print(combination);
        serial_print("\n");
    }
}

void comparedKey() {
    acumulatedTime += TIME_INCREMENT_MS;

    if (!enterButton) {
        if (systemState == ON) {
            serial_print("Ingrese la clave para desbloquear.\n");
        } else {
            serial_print("Ingrese la clave para bloquear.\n");
        }

        buttonTask(input_combination);

        if (strcmp(combination, input_combination) == 0) {
            if (systemState == ON) {
                serial_print("¡Combinación correcta! Sistema desbloqueado.\n");
                systemState = OFF;
                buzzerState = ON;
                buzzerTimeOn = 300;  // Configuración del tiempo del buzzer
            } else {
                serial_print("¡Combinación correcta! Sistema bloqueado.\n");
                systemState = ON;
                buzzerState = ON;
                buzzerTimeOn = 300;  // Configuración del tiempo del buzzer
            }
            tryNumber = 0; // Resetear el contador de intentos fallidos
        } else {
            tryNumber++;
            if (tryNumber >= 3) {
                serial_print("¡Sistema bloqueado por demasiados intentos fallidos!\n");
                buzzerState = ON;
                buzzerTimeOn = 600;  // Configuración del tiempo del buzzer
            } else {
                buzzerState = ON;
                buzzerTimeOn = 500;  // Configuración del tiempo del buzzer
                serial_print("Combinación incorrecta: ");
                serial_print(input_combination);
                serial_print("\nIntentos restantes: ");
                char try_left = '0' + (3 - tryNumber);
                serial_port.write(&try_left, 1);
                serial_print("\n");
            }
        }
    }

    if (acumulatedTime >= TIME_MAX_BLINKING_MS && systemState) {
        systemLed = !systemLed;
        acumulatedTime = 0;
    }
}

void ldrTask() {
    LDR_value = LDR.read(); // Lee el valor analógico del LDR
    if (LDR_value > LDR_THRESHOLD_OFF) {
        lamp = OFF;  // Apagar el foco si el valor del LDR es mayor que el umbral de apagado
    } else if (LDR_value < LDR_THRESHOLD_ON) {
        lamp = ON;  // Encender el foco si el valor del LDR es menor que el umbral de encendido
    }
}
