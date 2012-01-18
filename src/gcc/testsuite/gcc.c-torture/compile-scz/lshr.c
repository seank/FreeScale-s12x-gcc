unsigned long global;

unsigned long ashr(unsigned long a, short b)
{
  a = a >> b;
  global = a >> 1;
  return a;
}
