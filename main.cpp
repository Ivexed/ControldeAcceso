#include "mbed.h"
#include "arm_book_lib.h"
#include "control.h"

// main() runs in its own thread in the OS
int main()
{
    accessControlInit();
    while (true) {
        accessControlUpdate();
    }
}

