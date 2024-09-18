#ifndef _KEY_H
#define _KEY_H

#define KEYPAD_NUMBER_OF_ROWS    4
#define KEYPAD_NUMBER_OF_COLS    4
#define DEBOUNCE_MS              120
#define MAX_COMBINATION_SIZE     4


void keyInit( int updateTime_ms );
char KeyUpdate();
static char keyget();
static void keyReset();





//=====[#include guards - end]=================================================

#endif 

