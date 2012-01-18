#include <stdio.h>
#include <setjmp.h>

jmp_buf jbuf;
int jret;

int
fact (int n)
{
  if (n <= 1)
    {
      if (jret)
        longjmp (jbuf, jret);
      
      return 1;
    }
  else
    {
      return fact (n - 1) * n;
    }
}

int
compute (int n)
{
  int result;

  result = setjmp (jbuf);
  if (result != 0)
    return result;

  result = fact (n);
  return result * n;
}

int
main ()
{
  int result;

  result = compute (4);
  if (result != 96)
    abort ();
  
  jret = 23;
  result = compute (4);
  if (result != 23)
    abort ();
  return 0;
}
