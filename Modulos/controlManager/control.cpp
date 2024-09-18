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
#include "rele/rele.h"

DigitalOut systemLed(D3); // salida digital para el led indicador de sistema

#define TIME_MAX_BLINKING_MS 1000  // 1 segundo

static bool systemState;
int  acumulatedTime = 0;
extern char combination[MAX_COMBINATION_SIZE + 1];

void accessControlInit();
void accessControlUpdate();
void system();

void accessControlInit()
{
    buzzerInit();
    keyInit( SYSTEM_TIME_INCREMENT_MS  );
    ldrInit();
    releInit();
    uart_init();
    systemLed = ON;
    interfaceDisplayInit();
    initializeDefaultDateTime();
    setSystemState(true);//true -> sistema bloqueado
                         //false -> sistema desbloqueado

}

void setSystemState(bool sysstate) {
    systemState = sysstate;
}
bool getSystemState() {
    return systemState;
}

void system(){
    acumulatedTime += SYSTEM_TIME_INCREMENT_MS;
    if (acumulatedTime >= TIME_MAX_BLINKING_MS && systemState) {
        systemLed = !systemLed;
        acumulatedTime = 0;
    } else if (!systemState) {
        systemLed = ON;
    }
}


void accessControlUpdate()
{
    ldrTask();
    system();
    comparedKey();
    buzzerTask();
    checkDisplayConditions();
    interfaceDisplayUpdate();
    releTask();
    delay(SYSTEM_TIME_INCREMENT_MS);
}
