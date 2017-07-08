#pragma once


#include <stdio.h>

long millis();


class HardwareSerial
{
public:
    void begin(long speed);
    void print(const char *);
    void println(const char *);
    void println(size_t);
};


extern HardwareSerial Serial;


int analogRead(int pin);


#define strlen_P(str)   strlen(str)

typedef void *PGM_VOID_P;

#define memcpy_P(a, b, l)       memcpy(a, b, l)
#define memccpy_P(a, b, c, l)   memccpy(a, b, c, l)

#define	A0	0
#define	D8	8