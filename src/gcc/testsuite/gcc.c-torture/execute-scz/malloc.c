#include <stdlib.h>
#include <string.h>

int main()
{
  char *p[100];
  int i, j;
  
  for (i = 0; i < 100; i++)
    {
      p[i] = malloc (40);
      /* printf ("p[%d] = 0x%02x\n", i, p[i]); */
    }

  for (i = 0; i < 10; i++)
    for (j = 0; j < 32; j++)
      p[i][j] = i + j + ' ';

  for (i = 0; i < 10; i++)
    p[i][32] = 0;

  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      if (i == j)
        {
          if (strcmp (p[i], p[j]) != 0)
            return 1;
        }
      else if (strcmp (p[i], p[j]) == 0)
        return 1;
  return 0;
}
