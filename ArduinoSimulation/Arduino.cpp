#include "Arduino.h"

#include <WString.h>
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

void HardwareSerial::println(const char * str)
{
    printf("%s\n", str);
}

void HardwareSerial::println(size_t val)
{
    println(String(val).c_str());
}



int analogRead(int pin)
{
	static int last_value = 0;

	last_value = (last_value + 7) % 1024;

	return last_value;
}