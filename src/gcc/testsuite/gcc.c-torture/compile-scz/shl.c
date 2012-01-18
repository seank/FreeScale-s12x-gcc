unsigned long shl(unsigned long a, int b)
{
  a = a >> b;
  bar(b);
  return a;
}
