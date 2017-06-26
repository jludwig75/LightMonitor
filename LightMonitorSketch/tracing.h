#ifndef __TRACING_H__
#define __TRACING_H__


void enable_serial_tracing(long speed);

void inf_printf(const char *format, ...);
void err_printf(const char *format, ...);


#endif  // __TRACING_H__
