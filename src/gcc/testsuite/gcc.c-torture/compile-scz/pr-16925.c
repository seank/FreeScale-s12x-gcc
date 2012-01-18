/* PR target/16925: ICE on 64-bit host architectures */
typedef unsigned int UDItype __attribute__ ((mode (DI)));

void ICE_on_64bit_archs (void)
{
  UDItype a;
  a |= 0x8000000000000LL;
}

