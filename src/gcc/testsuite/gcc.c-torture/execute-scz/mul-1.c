unsigned char
frac_char (unsigned char n)
{
  if (n > 1)
    return n * frac_char (n - 1);
  else
    return 1;
}

unsigned short
frac_ushort (unsigned short n)
{
  if (n > 1)
    return n * frac_ushort (n - 1);
  else
    return 1;
}

short
frac_short (short n)
{
  if (n > 1)
    return n * frac_short (n - 1);
  else
    return 1;
}

unsigned long
frac_ulong (unsigned long n)
{
  if (n > 1)
    return n * frac_ulong (n - 1);
  else
    return 1;
}

long
frac_long (long n)
{
  if (n > 1)
    return n * frac_long (n - 1);
  else
    return 1;
}

unsigned long long
frac_ulonglong (unsigned long long n)
{
  if (n > 1)
    return n * frac_ulonglong (n - 1);
  else
    return 1;
}

long long
frac_longlong (long long n)
{
  if (n > 1)
    return n * frac_longlong (n - 1);
  else
    return 1;
}

long long ftable[] = {
  1, 2, 6, 24, 120, 720, 5040, 40320, 362880,
  3628800, 39916800, 479001600, 6227020800,
  87178291200, 1307674368000, 20922789888000,
  355687428096000, 6402373705728000, 121645100408832000,
  2432902008176640000
};

void
error (char *func, int n, long long result)
{
  printf ("Failed: %s (%d) => %lld\n", func, n, result);
  exit (1);
}

int
main ()
{
  int i;

  for (i = 0; i < sizeof(ftable) / sizeof(ftable[0]); i++)
    {
      if (ftable[i] < 256)
	{
	  if (frac_char (i+1) != ftable[i])
	    error ("frac_char", i, (long long) frac_char (i+1));
	}
      if (ftable[i] < 65536)
	{
	  if (ftable[i] <= 32767 && frac_short (i+1) != ftable[i])
	    error ("frac_short", i, (long long) frac_short (i+1));

	  if (frac_ushort (i+1) != ftable[i])
	    error ("frac_ushort", i, (long long) frac_ushort (i+1));
	}
      if (ftable[i] < 65536*65536)
	{
	  if (ftable[i] <= 0x7ffffffffL && frac_long (i+1) != ftable[i])
	    error ("frac_long", i, (long long) frac_long (i+1));

	  if (frac_ulong (i+1) != ftable[i])
	    error ("frac_ulong", i, (long long) frac_ulong (i+1));
	}
      if (frac_longlong (i+1) != ftable[i])
	error ("frac_longlong", i, frac_longlong (i+1));

      if (frac_ulonglong (i+1) != ftable[i])
	error ("frac_ulonglong", i, frac_ulonglong (i+1));      
    }
  return 0;
}
