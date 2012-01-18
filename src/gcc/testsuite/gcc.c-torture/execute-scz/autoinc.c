void
post_inc_short (unsigned short *dst, unsigned short *src)
{
  *dst++ = *src++;
  *dst++ = 0xabcd;
  *dst++ = src[2];
  *dst = *src++;
}

void
pre_inc_short (unsigned short *dst, unsigned short *src)
{
  *++dst = *++src;
  *++dst = 0xabcd;
  *++dst = src[3];
  *++dst = *++src;
}


void
post_inc_long (unsigned long *dst, unsigned long *src)
{
  *dst++ = *src++;
  *dst++ = 0xabcdef23;
  *dst++ = src[2];
  *dst = *src++;
}

void
pre_inc_long (unsigned long *dst, unsigned long *src)
{
  *++dst = *++src;
  *++dst = 0xabcdef23;
  *++dst = src[3];
  *++dst = *++src;
}

int
main ()
{
  unsigned short dst[10];
  unsigned short src[10];
  unsigned long dstl[10];
  unsigned long srcl[10];

  src[0] = 0x1234;
  src[1] = 0x2345;
  src[3] = 0x3456;
  src[4] = 0x4567;
  post_inc_short (dst, src);
  if (dst[0] != 0x1234 || dst[1] != 0xabcd
      || dst[2] != 0x3456 || dst[3] != 0x2345)
    abort ();

  srcl[0] = 0x12345678;
  srcl[1] = 0x23456789;
  srcl[3] = 0x3456789a;
  srcl[4] = 0x456789ab;
  post_inc_long (dstl, srcl);
  if (dstl[0] != 0x12345678 || dstl[1] != 0xabcdef23
      || dstl[2] != 0x3456789a || dstl[3] != 0x23456789)
    abort ();

  pre_inc_long (dstl, &srcl[-1]);
  if (dstl[1] != 0x12345678 || dstl[2] != 0xabcdef23
      || dstl[3] != 0x3456789a || dstl[4] != 0x23456789)
    abort ();

  return 0;
}
