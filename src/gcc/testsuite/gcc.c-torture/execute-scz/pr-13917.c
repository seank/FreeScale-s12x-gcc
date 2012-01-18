#include <string.h>

void ltoa(char *buf, unsigned long i, int base);

void ltoa(char *buf, unsigned long i, int base)
{
  char *s;
#define LEN 25
  int rem;
  char rev[LEN+1];

  if (i == 0)
    s = "0";
  else
    {
      rev[LEN] = 0;
      s = &rev[LEN];
      while (i)
        {
          rem = i % base;
          if (rem < 10)
            *--s = rem + '0'; // >>>>>>>> Here appears the error.
          else
            if (base == 16)
              *--s = "abcdef"[rem - 10];
          i /= base;
        }
    }
  strcpy(buf, s);
}

int main()
{
  char buf[32];

  ltoa(buf, 0x123456, 10);
  if (strcmp(buf, "1193046") != 0)
    return 1;
  
  ltoa(buf, 0x2345678, 13);
  if (strcmp(buf, "7870") != 0)
    return 1;
  
  ltoa(buf, 0xabcdef0, 16);
  if (strcmp(buf, "abcdef0") != 0)
    return 1;
  
  /* Also check that the strcmp detects strings not equal!  */
  return strcmp(buf, "bcde") != 0 ? 0 : 1;
}
