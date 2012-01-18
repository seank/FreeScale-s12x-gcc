unsigned short uminhi(unsigned short a, unsigned short b)
{
  a = (a < b) ? a : b;
  return a;
}

unsigned short umaxhi(unsigned short a, unsigned short b)
{
  a = (a > b) ? a : b;
  return a;
}

unsigned char e;

void
umaxqi(unsigned char a)
{
  e = (a > e) ? e : a;
}

unsigned char
umaxqi2(unsigned char a)
{
  a = (a > e) ? e : a;
  return a;
}

void
uminqi(unsigned char a)
{
  e = (a < e) ? e : a;
}

unsigned char
uminqi2(unsigned char a)
{
  a = (a < e) ? e : a;
  return a;
}
