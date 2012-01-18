/*  scanner.c */
/*  J. Tritthardt, MPIMF/BMO */
/*  Version 1.0 - 28.02.2002 */

/*  Testprogramm fuer die LEDs der Scanner-Box */

#define COPCTL *(volatile unsigned char *)(0x16)

#define IO_BASE 0
#define PORTT *((volatile unsigned char *)(IO_BASE + 0xAE))
#define DDRT *((volatile unsigned char *)(IO_BASE + 0xAF))

#define led_red 0x02
#define led_red_port PORTT
#define led_red_ddr DDRT
#define led_green 0x08
#define led_green_port PORTT
#define led_green_ddr DDRT

void delay();

int main() 
{ 
  led_red_port = led_red_port | led_red;
  led_red_ddr = led_red_ddr | led_red;
  led_green_port = led_green_port | led_green;
  led_green_ddr = led_green_ddr | led_green;

  while (1) {
    led_red_port = led_red_port | led_red;
    led_green_port = led_green_port & ~led_green;

    delay();

    led_green_port = led_green_port | led_green;
    led_red_port = led_red_port & ~led_red;

    delay();
  }

  return 0;
} 
 
void __premain() 
{
    __asm__ __volatile__ ("clr 0x16");
} 

void delay()
{
#ifdef mc6812
  __asm__ __volatile__ ("PSHD\n\tLDD	0xFFFF\n\tDBNE	D,-3\n\tPULD\n\tRTS");
#endif
#ifdef mc6811
  __asm__ __volatile__ ("PSHA\n\tLDD	0xFFFF\n\tPULA\n\tRTS");
#endif
}
