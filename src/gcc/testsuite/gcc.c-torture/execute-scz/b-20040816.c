typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

uint32_t test;

void shl(uint8_t Nr)
{
    test |= (1L<<Nr);
}
 
int main(void)
{
  test = 1;
  shl(2);
  if (test != 5L)
     return 1;
  shl(17);
  if (test != (5L | (1L << 17)))
     return 1;
  return 0;
}
