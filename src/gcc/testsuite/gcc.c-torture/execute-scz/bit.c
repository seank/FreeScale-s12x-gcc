unsigned
bit_char (unsigned char n)
{
  unsigned cnt = 0;

  if (n & 1) cnt++;
  if (n & 2) cnt++;
  if (n & 4) cnt++;
  if (n & 8) cnt++;
  if (n & 16) cnt++;
  if (n & 32) cnt++;
  if (n & 64) cnt++;
  if (n & 128) cnt++;
  return cnt;
}

unsigned
bit_short (unsigned short n)
{
  unsigned cnt = 0;

  if (n & 1) cnt++;
  if (n & 128) cnt++;
  if (n & 256) cnt++;
  if (n & 0x8000) cnt++;

  return cnt + bit_char (n) + bit_char (n >> 8);
}

unsigned
bit_ulong (unsigned long n)
{
  unsigned cnt = 0;

  if (n & 1) cnt++;
  if (n & 0x8000) cnt++;  
  if (n & 0x10000) cnt++;
  if (n & 0x80000000) cnt++;
  return cnt + bit_short (n) + bit_short (n >> 16);
}

unsigned
bit_ulonglong (unsigned long long n)
{
  unsigned cnt = 0;

  if (n & 1LL) cnt++;
  if (n & 0x80000000LL) cnt++;  
  if (n & 0x100000000LL) cnt++;
  if (n & 0x8000000000000000LL) cnt++;
  return cnt + bit_ulong (n) + bit_ulong (n >> 32);
}

int
main ()
{
  long long n;
  int i, j;
  unsigned cnt_char, cnt_short, cnt_long, cnt_longlong;
  
  for (i = 0; i < 64; i++)
    {
      n = (1LL << i);
      cnt_char = 0;
      cnt_short = 0;
      cnt_long  = 0;
      cnt_longlong = bit_ulonglong (n);
      for (j = 0; j < 8; j++)
	{
	  cnt_char += bit_char (n >> (j * 8));
	  if ((j & 1) == 0)
	    cnt_short += bit_short (n >> (j * 8));

	  if ((j & 3) == 0)
	    cnt_long += bit_ulong (n >> (j * 8));
	}
#if 0
      printf ("%d: %d %d %d %d\n", i, cnt_char, cnt_short,
	      cnt_long, cnt_longlong);
#endif
      if ((i % 8) == 0 || (i % 8) == 7)
	cnt_short --, cnt_long --, cnt_longlong --;

      if ((i % 16) == 0 || (i % 16) == 15)
	cnt_long --, cnt_longlong --;

      if ((i % 32) == 0 || (i % 32) == 31)
	cnt_longlong --;

      if (cnt_short != cnt_char || cnt_short != cnt_long
	  || cnt_long != cnt_longlong || cnt_char != 1)
	exit (1);
    }
  return 0;
}
