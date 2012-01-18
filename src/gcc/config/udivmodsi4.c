unsigned long
__udivmodsi4 (unsigned long num, unsigned long den, unsigned long* mod)
{
  unsigned long bit;
  unsigned long res;
  
  if ((unsigned short) (den >> 16) == 0)
    {
#ifdef mc68hc11
      if ((unsigned short) (num >> 16) == 0)
        {
          /* Both numbers are 16-bit quantities, use 16-bit div/mod.  */
          unsigned short sden = (unsigned short) den;
          unsigned short snum = (unsigned short) num;
          unsigned short sres = snum / sden;
          unsigned short smod = snum % sden;;

          if (mod)
            *mod = (unsigned long) smod;
          return (unsigned long) sres;
        }
#endif
#ifdef mc68hc12
        {
          /* To avoid to stress the gcc reload, use + operand modifier
             and pass the input values in the same variables as the
             outputs.  */
          unsigned short status = (unsigned short) den;
          unsigned short smod = (unsigned short) (num & 0x0ffff);
          unsigned short sres = (unsigned short) (num >> 16);

          __asm__ __volatile__ ("ediv\n"
                                "tfr ccr,x"
                                : "+x" (status), "+y" (sres),
                                  "+d" (smod));
          /* check for overflow */
          if (!(status & 0x03))
            {
              if (mod)
                *mod = (unsigned long) smod;
              return (unsigned long) sres;
            }
        }
#endif
      if ((unsigned short) den == 0)
        {
          if (mod)
            *mod = 0;
          return 0;
        }
    }
  bit = 1;
  res = 0;
  while (den < num && !((unsigned short) (den >> 16) & (1L<<15)))
    {
      den <<=1;
      bit <<=1;
    }
  while (bit)
    {
      if (num >= den)
	{
	  num -= den;
	  res |= bit;
	}
      bit >>=1;
      den >>=1;
    }
  if (mod)
    *mod = num;
  return res;
}

#ifdef L_udivmodsi4
unsigned long
udivmodsi4 (unsigned long num, unsigned long den, int modwanted)
{
  unsigned long mod;

  if (modwanted)
    {
      __udivmodsi4 (num, den, &mod);
      return mod;
    }
  else
    {
      return __udivmodsi4 (num, den, 0);
    }
}
#endif
