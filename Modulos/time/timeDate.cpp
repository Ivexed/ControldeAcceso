#include "mbed.h"
#include "timeDate.h"
#include "display.h"
#include "serial.h"
#include "key.h"

// Valores por defecto
#define DEFAULT_YEAR 2024
#define DEFAULT_MONTH 9
#define DEFAULT_DAY 16
#define DEFAULT_HOUR 0
#define DEFAULT_MINUTE 0
#define DEFAULT_SECOND 0

// Función para establecer la fecha y hora por defecto
void initializeDefaultDateTime()
{
    dateAndTimeWrite(DEFAULT_YEAR, DEFAULT_MONTH, DEFAULT_DAY, 
                     DEFAULT_HOUR, DEFAULT_MINUTE, DEFAULT_SECOND);
}

// Funciones de lectura y escritura de fecha y hora
char* dateAndTimeRead()
{
    time_t epochSeconds;
    epochSeconds = time(NULL);
    return ctime(&epochSeconds);    
}

void dateAndTimeWrite(int year, int month, int day, 
                      int hour, int minute, int second)
{
    struct tm rtcTime;

    rtcTime.tm_year = year - 1900;
    rtcTime.tm_mon  = month - 1;
    rtcTime.tm_mday = day;
    rtcTime.tm_hour = hour;
    rtcTime.tm_min  = minute;
    rtcTime.tm_sec  = second;

    rtcTime.tm_isdst = -1;

    set_time(mktime(&rtcTime));
}

