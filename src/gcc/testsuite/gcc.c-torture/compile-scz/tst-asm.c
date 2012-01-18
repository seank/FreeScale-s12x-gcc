void __premain()
{
  __asm__ volatile("clra\n\t"
	                     "tap" : : : "d");
}

void inline foo()
{
  char* msg = "TEST STRING";
  unsigned char code = 16;
  
  __asm__ __volatile__("jsr  0x7012"
                       : : "x"(msg), "d"(code));
}

int main()
{
  ;
}
