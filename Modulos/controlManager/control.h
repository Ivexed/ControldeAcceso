#ifndef _CONTROL_H
#define _CONTROL_H


#define SYSTEM_TIME_INCREMENT_MS   10

void accessControlInit();
void accessControlUpdate();
bool getSystemState();
void setSystemState(bool sysstate);
void system();
//=====[#include guards - end]=================================================

#endif 