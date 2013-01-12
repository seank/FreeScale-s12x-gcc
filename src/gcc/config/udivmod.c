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

unsigned long
__inline __udivsi3 (unsigned long a, unsigned long b)
{
  return __udivmodsi4 (a, b, 0);
}

unsigned long
__inline __umodsi3 (unsigned long a, unsigned long b)
{
  unsigned long mod;

  __udivmodsi4 (a, b, &mod);
  return mod;
}



#endif /* !mc68hc12 */
