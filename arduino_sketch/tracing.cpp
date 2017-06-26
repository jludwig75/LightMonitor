#include "tracing.h"

#include <stdarg.h>
#include <Arduino.h>


void enable_serial_tracing(long speed)
{
  Serial.begin(speed);
}


void inf_printf(const char *format, ...)
{
  va_list arg;
  va_start(arg, format);

  char temp[64];
  char* buffer = temp;

  size_t len = vsnprintf(temp, sizeof(temp), format, arg);
  va_end(arg);
  if (len > sizeof(temp) - 1)
  {
    buffer = new char[len + 1];
    if (!buffer) {
      return;
    }
    va_start(arg, format);
    vsnprintf(buffer, len + 1, format, arg);
    va_end(arg);
  }
  Serial.print(buffer);
  if (buffer != temp) {
    delete[] buffer;
  }
}

void err_printf(const char *format, ...)
{
  va_list ap;

  va_start(ap, format);
  inf_printf(format, ap);

  va_end(ap);
}

