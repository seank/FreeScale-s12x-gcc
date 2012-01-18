unsigned int segwerte[9];
void me_Measure_seg();
void ser_putword( unsigned int data );

void command_messen(void)
{
 // volatile int i;
 int i;
 me_Measure_seg();
 for(i=0;i<9;i++)
  {
   ser_putword(segwerte[i]);
  }
}
