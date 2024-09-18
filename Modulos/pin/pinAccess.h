#ifndef _PINACCESS_H
#define _PINACCESS_H


#define MAX_COMBINATION_SIZE 4      // Tamaño máximo de la combinación de botones

void comparedKey();
void setSystemTime();


int getTryNumber();
bool getIncorrectCodeState();
char getInputCombination();

bool isAwaitingInput();
void setAwaitingInput(bool value);

bool isChangingCombination();
void setChangingCombination(bool value);

int getNumberOfChars();

void setClockShow(bool value);
bool getClockShow();

void setTime(bool set);
bool getSetTime();

bool getPressedKey();

//=====[#include guards - end]=================================================

#endif 