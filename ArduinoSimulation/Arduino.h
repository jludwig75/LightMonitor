#pragma once


#include <stdio.h>

long millis();


class HardwareSerial
{
public:
    void begin(long speed);
    void print(const char *);
};


extern HardwareSerial Serial;


int analogRead(int pin);