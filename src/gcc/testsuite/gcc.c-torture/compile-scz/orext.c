unsigned long b;
unsigned char c;
unsigned char d;

unsigned short get()
{
  return (c << 8) | d;
}

unsigned long orext(unsigned long a)
{
  a = (b >> 16) | a;
  a = a | c;
  a = a | (unsigned long) ((d | (c << 8)));
  return a;
}
