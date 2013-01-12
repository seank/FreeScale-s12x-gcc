/* cover the root directory case */
#if !defined(mc68hc11) && !defined(mc68hc12) && !defined(m9s12x)
#if defined(target11)
#define mc68hc11
#endif
#if defined(target12)
#define mc68hc12
#endif
#if defined(targets12x)
#define m9s12x
#define mc68hc12
#endif
#endif

#ifndef mc68hc12

extern unsigned long __udivmodsi4 (unsigned long num, unsigned long den,
                                   unsigned long *mod);

long
__divsi3 (long a, long b)
{
  int neg = 0;
  long res;

  if (a < 0)
    {
      a = -a;
      neg = !neg;
    }

  if (b < 0)
    {
      b = -b;
      neg = !neg;
    }

  res = __udivmodsi4 (a, b, 0);

  if (neg)
    res = -res;

  return res;
}

long
__modsi3 (long a, long b)
{
  int neg = 0;
  long res;

  if (a < 0)
    {
      a = -a;
      neg = 1;
    }

  if (b < 0)
    b = -b;

  __udivmodsi4 (a, b, (unsigned long*) &res);

  if (neg)
    res = -res;

  return res;
}


#endif /* !mc68hc12  */
