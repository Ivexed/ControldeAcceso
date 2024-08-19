#include "mbed.h"
#include "arm_book_lib.h"
#include <string.h>

UnbufferedSerial serial_port(USBTX, USBRX); // Definimos la UART

void uart_init() {
    serial_port.baud(112500);

}


void serial_print(const char* str) {
    serial_port.write(str, strlen(str));
}

