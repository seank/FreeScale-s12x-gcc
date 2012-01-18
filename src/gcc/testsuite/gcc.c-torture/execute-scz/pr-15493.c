#ifdef mc68hc1x
/* The softregs start at address 0.  The test needs to write
   at 0x0 to verify that the 'mebi->dirX = 0' are fixed.
   We use this padding scratch area to make sure the soft
   registers do not start at 0. */
char __attribute__((section(".page0"))) scratch[0x20] = { 0 };
#endif

typedef struct
{
   volatile unsigned char portA;
   volatile unsigned char  portB;
   volatile unsigned char  dirA;
   volatile unsigned char  dirB;
} MEBI_Regs;

void ReadExternalBus( unsigned int addr )
{
   MEBI_Regs *mebi = (MEBI_Regs*)0;

   // Write the address to the port A and B registers
   mebi->portB = addr;
   mebi->portA = addr>>8;

   // Change ports A and B to inputs
   mebi->dirA = 0;
   mebi->dirB = 0;
}

void check(MEBI_Regs* p, unsigned char a, unsigned char b)
{
  if (p->portA != a)
    abort();
  if (p->portB != b)
    abort();
  if (p->dirA != 0)
    abort();
  if (p->dirB != 0)
    abort();
}

int main( void )
{
#ifdef mc68hc1x
  char* p = (char*) 0;
  unsigned short i;
  
  for (i = 0x20; i > 0; i--)
    *p++ = 0xaa;

#endif
  ReadExternalBus( 0x1000 );
#ifdef mc68hc1x
  check(0, 0x10, 0);
#endif
  return 0;
}
