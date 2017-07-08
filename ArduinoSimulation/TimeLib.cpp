#define _CRT_SECURE_NO_WARNINGS
#include <TimeLib.h>

#include <time.h>
#include <stdint.h>
#include <string.h>


void setTime(time_t time)
{

}

time_t now()
{
    return time(NULL);
}

void breakTime(time_t time, tmElements_t &tm)
{
    struct tm * t = localtime(&time);

    memset(&tm, 0, sizeof(tm));

    tm.Year = (t->tm_year + 1900) - 1970;
    tm.Month = t->tm_mon + 1;
    tm.Day = t->tm_mday;
    tm.Hour = t->tm_hour;
    tm.Minute = t->tm_min;
    tm.Second = t->tm_sec;
    tm.Wday = t->tm_wday;
}
