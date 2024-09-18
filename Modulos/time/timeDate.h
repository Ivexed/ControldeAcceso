//=====[#include guards - begin]===============================================

#ifndef _TIMEDATE_H_
#define _TIMEDATE_H_


char* dateAndTimeRead();

void dateAndTimeWrite( int year, int month, int day, 
                       int hour, int minute, int second );

void initializeDefaultDateTime();

#endif // _TIMEDATE_H_