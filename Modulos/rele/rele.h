#ifndef _RELE_H
#define _RELE_H

#define RELE_TIME_MS 100


void releTask();
void releInit();

void setReleLockState(bool rel);
bool getReleLockState();


#endif 