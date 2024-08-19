#include "mbed.h"
#include "arm_book_lib.h"
#include "control.h"

int main() {
    accessControlInit();

    while (true) {
        accessControlUpdate();
    }
}