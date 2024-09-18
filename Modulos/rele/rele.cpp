#include "control.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "rele/rele.h"

DigitalOut rel(D13);   //salida digital para activar un rele

static bool releLockState;

void releInit(){
    rel = OFF;
    setReleLockState(false);
}
void setReleLockState(bool relState){
    releLockState = relState;
}
bool getReleLockState(){
    return releLockState;
}

void releTask(){
    int acummulatedReleTime = 0;
    if(releLockState){
        rel = ON;
        acummulatedReleTime += SYSTEM_TIME_INCREMENT_MS;
        if (acummulatedReleTime >= RELE_TIME_MS){
            rel = OFF;
            acummulatedReleTime = 0;
            setReleLockState(false);
        }
    }else{
        rel = OFF;
    }
}
