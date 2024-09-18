#include "mbed.h"
#include "arm_book_lib.h"
#include "key.h"
#include "serial.h"


typedef enum {
    KEY_SCAN,
    KEY_DEBOUNCE,
    KEY_HOLD
} keyState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalOut  row[KEYPAD_NUMBER_OF_ROWS]  = {D11, D10, D9, D8};
DigitalIn   Col[KEYPAD_NUMBER_OF_COLS]  = {D7, D6, D5, D4};

static keyState_t states;
static int increment_Time_ms = 0;

static char keyget();
static void keyReset();
void keyInit();
char KeyUpdate();


void keyInit( int updateTime_ms )
{
    increment_Time_ms = updateTime_ms;
    states = KEY_SCAN;
    int index = 0;
    for( index=0; index < KEYPAD_NUMBER_OF_COLS; index++ ) {
        (Col[index]).mode(PullUp);
    }
}

char KeyUpdate()
{
    static int debounceTimeCounterAccumulator = 0;
    static char LastKeyPressed = '\0';

    char key_get = '\0';
    char key_free = '\0';

    switch( states ) {

    case KEY_SCAN:
        key_get = keyget();
        if( key_get != '\0' ) {
            LastKeyPressed = key_get;
            debounceTimeCounterAccumulator = 0;
            states = KEY_DEBOUNCE;
        }
        break;

    case KEY_DEBOUNCE:
        if( debounceTimeCounterAccumulator >= DEBOUNCE_MS ) {
            key_get = keyget();
            if( key_get == LastKeyPressed ) {
                states = KEY_HOLD;
            } else {
                states = KEY_SCAN;
            }
        }
        debounceTimeCounterAccumulator = debounceTimeCounterAccumulator + increment_Time_ms;
        break;

    case KEY_HOLD:
        key_get = keyget();
        if( key_get != LastKeyPressed ) {
            if( key_get == '\0' ) {
                key_free = LastKeyPressed;
            }
            states = KEY_SCAN;
        }
        break;

    default:
        keyReset();
        break;
    }
    return key_free;
}

static char keyget()
{
    int fila = 0;
    int columna = 0;
    int i = 0; 

    char KeypadToCharArray[] = {
        '1', '2', '3', 'A',
        '4', '5', '6', 'B',
        '7', '8', '9', 'C',
        '*', '0', '#', 'D',
    };

    for( fila=0; fila< KEYPAD_NUMBER_OF_ROWS; fila++ ) {

        for( i=0; i< KEYPAD_NUMBER_OF_ROWS; i++ ) {
            row[i] = ON;
        }

        row[fila] = OFF;

        for( columna=0; columna < KEYPAD_NUMBER_OF_COLS; columna++ ) {
            if( Col[columna] == OFF ) {
                return KeypadToCharArray[fila*KEYPAD_NUMBER_OF_ROWS + columna];
            }
        }
    }
    return '\0';
}

static void keyReset()
{
    states = KEY_SCAN;
}
