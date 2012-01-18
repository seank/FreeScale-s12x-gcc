#include <stddef.h>

void copy(short *s, short *q, size_t l)
{
  while (--l > 0) *s++ = *q++;
}
