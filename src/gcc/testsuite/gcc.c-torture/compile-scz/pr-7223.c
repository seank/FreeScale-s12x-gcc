
extern int foo(int);

int main(int argn, char ** argv)
{
        char i;
        int pos;
        short d, e, f;

        for(i=100;i>0;--i){
                argn += i;
        }

        e = (short)i-argn;
        d = argn / 1000;

        pos = foo(d * e);

        (*(((unsigned char *)0x1000)+(0x00))) |= 0x10;

        return argn;
}
