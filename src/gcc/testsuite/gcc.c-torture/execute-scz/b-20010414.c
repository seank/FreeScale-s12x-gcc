enum v {
  L1, L2, L3
};
void bar();

int
get(unsigned char a, unsigned char b, long *c, enum v d)
{
  int i, j;

  bar ();
  switch (d)
    {
    case L1:
      i = 1;
      break;

    case L2:
      i = b;
      break;

    case L3:
      i = *c;
      break;
    }
  j = 0;
  while (i > 0)
    {
      j += i;
      i--;
    }
  return j;
}

void
bar()
{
  ;
}

int
main ()
{
  long a = 0x12345678;
  int result;
  
  result = get (1, 2, &a, L2);
  if (a != 0x12345678)
    abort ();

  if (result != 3)
    abort ();
  
  return 0;
}
