#include "mbed.h"
#include "arm_book_lib.h"
#include <string.h>

// Defino el nivel de umbral del LDR
#define LDR_LEVEL 0.5

//================ Object declaration ============================
// Defino los pines de salida digital para cada caso
DigitalOut systemLed(D4);
DigitalOut lamp(D7);
DigitalOut buzzer(D8);

// Defino los pines de entrada digital para los botones
DigitalIn button1(D10);
DigitalIn button2(D11);
DigitalIn button3(D12);
DigitalIn button4(D13);
DigitalIn enterButton(BUTTON1);  // Botón de Enter

// Definimos la entrada analógica del LDR
AnalogIn LDR(A0);

// Definimos la UART
UnbufferedSerial serial_port(USBTX, USBRX);

//================ Global Variables =============
bool systemState = ON;
int tryNumber = 0;
#define MAX_COMBINATION_SIZE 4 // Tamaño máximo de la combinación de botones
// Buffer para almacenar la combinación de botones
char combination[MAX_COMBINATION_SIZE + 1]; // Añadimos un espacio adicional para el caracter nulo
char input_combination[MAX_COMBINATION_SIZE + 1]; // Añadimos un espacio adicional para el caracter nulo
static bool locked = OFF;
float LDR_value;

//===== Declaraciones (prototipos) de funciones ==========================
void uart_init();
void button_init();
void out_init();
void buttonTask(char* comb);
void comparedKey();
void passSet();
void serial_print(const char* str);
bool readButton(DigitalIn &button);
bool readEnterButton();
void ldrTask();
void sysResponse();
bool anyButtonPressed();
void wait_for_key_press();

//=============== Global init ======================
void serial_print(const char* str) {
    serial_port.write(str, strlen(str));
}

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

// Inicializo salidas
void out_init() {
    lamp = OFF;
    systemLed = ON;
    buzzer = ON;
    thread_sleep_for(30);
    buzzer = OFF;
}

bool readButton(DigitalIn &button) {
    if (button.read() == 1) {
        thread_sleep_for(50); // Esperar 50 ms para antirebote
        if (button.read() == 1) {
            return true;
        }
    }
    return false;
}

// Verifica si algún botón ha sido presionado
bool anyButtonPressed() {
    return readButton(button1) || readButton(button2) || readButton(button3) || readButton(button4);
}

// Verifica si se ha presionado el botón "Enter"
bool readEnterButton() {
    return readButton(enterButton);
}

// main() corre en su propio hilo en el OS
int main() {
    out_init();
    uart_init();
    button_init();

    while (true) {
        passSet();
        comparedKey();
        ldrTask();
        sysResponse();
    }
}

void buttonTask(char* comb) {
    int i = 0;
    while (i < MAX_COMBINATION_SIZE) {
        if (readButton(button1)) {
            comb[i++] = '1';
            serial_print("1 ");
        } else if (readButton(button2)) {
            comb[i++] = '2';
            serial_print("2 ");
        } else if (readButton(button3)) {
            comb[i++] = '3';
            serial_print("3 ");
        } else if (readButton(button4)) {
            comb[i++] = '4';
            serial_print("4 ");
        }
    }
    comb[i] = '\0'; // Añade terminador nulo al final de la cadena
}

void passSet() {
    static bool clavePin = false;

    if (!clavePin) {
        serial_print("Ingrese la combinación de botones (usando 1, 2, 3, 4):\n");
        buttonTask(combination);
        clavePin = true;
        serial_print("\nCombinación almacenada: ");
        serial_print(combination);
        serial_print("\n");
    }
}

void comparedKey() {
    if (!readEnterButton()) {
        if (systemState == ON) {
            serial_print("Ingrese la clave para desbloquear.\n");
            buttonTask(input_combination);
        } else {
            serial_print("Ingrese la clave para bloquear.\n");
            buttonTask(input_combination);
        }
        if (strcmp(combination, input_combination) == 0) {
            if (systemState == ON) {
                serial_print("¡Combinación correcta! Sistema desbloqueado.\n");
                systemState = OFF;
            } else {
                serial_print("¡Combinación correcta! Sistema bloqueado.\n");
                systemState = ON;
            }
            tryNumber = 0; // Resetear el contador de intentos fallidos
        } else {
            tryNumber++;
            if (tryNumber >= 3) {
                locked = ON;
                serial_print("¡Sistema bloqueado por demasiados intentos fallidos!\n");
            } else {
                buzzer = ON;
                thread_sleep_for(50);
                buzzer = OFF;
                serial_print("Combinación incorrecta: ");
                serial_print(input_combination);
                serial_print("\nIntentos restantes: ");
                char try_left = '0' + (3 - tryNumber);
                serial_port.write(&try_left, 1);
                serial_print("\n");
            }
        }
        //sysResponse();
    }
}

void sysResponse() {
    if (systemState == ON) {
        thread_sleep_for(300);
        systemLed = !systemLed;
        serial_print("Sistema en espera\n");
    } else {
        //systemLed = OFF;
        serial_print("¡Bienvenido!\n");
        systemLed = !systemLed;
        thread_sleep_for(1000);
    }
}

void ldrTask() {
    float ldrValue = LDR.read(); // Leer el valor analógico del LDR (0.0 a 1.0)
    if (ldrValue > LDR_LEVEL) {
        lamp = OFF;
        serial_print("Es de día.\n");
    } else {
        lamp = ON;
        serial_print("Es de noche.\n");
    }
}
