int main (void);
void Call1 (void);
unsigned char Var1         __attribute__ ((section (".page0")));
 
void _start (void)
{
 main();
}
 
int main (void)
{
 if (!Var1)
 {
  Call1();
 }
 Var1 |= 1;
return (0);
}
 
void Call1 (void)
{
}
