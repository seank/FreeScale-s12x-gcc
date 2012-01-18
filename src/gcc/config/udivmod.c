extern unsigned long __udivmodsi4 (unsigned long num, unsigned long den,
                                   unsigned long *mod);

unsigned long
__udivsi3 (unsigned long a, unsigned long b)
{
  return __udivmodsi4 (a, b, 0);
}

unsigned long
__umodsi3 (unsigned long a, unsigned long b)
{
  unsigned long mod;

  __udivmodsi4 (a, b, &mod);
  return mod;
}

