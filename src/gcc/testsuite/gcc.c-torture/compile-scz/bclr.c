#define bclr(m, o, b) \
    __asm __volatile("bclr %i1,%0 %2" : : "x" (m), "n" (o), "n" (b))
 
extern volatile unsigned char _io_ports[];
extern unsigned short toto;

void set(char* p)
{
  bclr(_io_ports, 0x30, 0x20);
  _io_ports[0x30] |= 0x20;
  p[2] |= 1;
  toto |= 4;
}
