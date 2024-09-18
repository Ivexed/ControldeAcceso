#ifndef _LDR_H
#define _LDR_H

#define RELE_TIME_MS 100

void ldrInit();
void ldrTask();


void setChanged(bool change);
bool isStateChanged();

void setLampState(bool lampst);
bool getLampState();


//=====[#include guards - end]=================================================

#endif 