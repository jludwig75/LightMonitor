#include "Arduino.h"

#include <stdio.h>
#include <Windows.h>


long millis()
{
    return GetTickCount();
}


HardwareSerial Serial;

void HardwareSerial::begin(long speed)
{

}

void HardwareSerial::print(const char * str)
{
    printf(str);
}


int analogRead(int pin)
{
    return 0;
}