/*
 *  compile with:
 * m6811-elf-gcc -mshort -O -fomit-frame-pointer -S test.c
 *          
 * Then notice that the generated code references the frame pointer,
 * even though we have told the compiler not to use it. The code is
 * correct if optimization is disabled.
 * */
            
void __attribute__((interrupt)) do_something(char *p1, char *p2);
            
void __attribute__((interrupt)) something(char *p1)
{
   char p2;
   char* p2p = &p2;
   do_something(p1, p2p);
}


