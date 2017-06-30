/*----------------------------------------------------------------------*
 * Arduino Timezone Library v1.0                                        *
 * Jack Christensen Mar 2012                                            *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/ 
#define _CRT_SECURE_NO_WARNINGS

#include "Timezone.h"

#include <time.h>

Timezone::Timezone(TimeChangeRule dstStart, TimeChangeRule stdStart)
{

}

Timezone::Timezone(int address)
{

}

time_t Timezone::toLocal(time_t utc)
{
    struct tm *t = localtime(&utc);
    return mktime(t);
}

time_t Timezone::toLocal(time_t utc, TimeChangeRule **tcr)
{
    struct tm *t = localtime(&utc);
    return mktime(t);
}

time_t Timezone::toUTC(time_t local)
{
    struct tm *t = gmtime(&local);
    return mktime(t);
}

//boolean Timezone::utcIsDST(time_t utc)
//{
//}
//
//boolean Timezone::locIsDST(time_t local)
//{
//}

void Timezone::readRules(int address)
{

}

void Timezone::writeRules(int address)
{

}

//void calcTimeChanges(int yr);
//time_t toTime_t(TimeChangeRule r, int yr);
