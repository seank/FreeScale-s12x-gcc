int main()
{
   
   unsigned short x;
   
   for (x=1; x<=0x8000; x++) 
     {
	
	asm volatile ("nop");
     }
   
   
   return 0;
}
