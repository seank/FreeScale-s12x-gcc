/*
 * Simple replacement of printf() for use by GCC testsuite.
 */
#include <stdarg.h>
#include <stddef.h>

extern int vsprintf(char*, const char*, ...);
extern int write(int, const char*, size_t);

int
printf(const char *fmt, ...)
{
  char buf[256];
  va_list args;
  int i;

  va_start(args, fmt);
  i=vsprintf(buf,fmt,args);
  va_end(args);

  write(0, buf, i);
  return i;
}

