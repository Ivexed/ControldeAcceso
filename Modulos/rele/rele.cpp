#include "control.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "rele/rele.h"
#include "serial.h"

DigitalOut rel(D13);   //salida digital para activar un rele

static bool releLockState;

void releInit(){
    rel = ON;
    setReleLockState(false);
}
void setReleLockState(bool relState){
    releLockState = relState;
}
bool getReleLockState(){
    return releLockState;
}

void releTask(){
    static int acummulatedReleTime = 0;
    if(releLockState){
        rel = OFF;
        setReleLockState(false);
        
    }else if(!getSystemState()){
        rel = OFF;
    }else{
        rel = ON;
    }
}
