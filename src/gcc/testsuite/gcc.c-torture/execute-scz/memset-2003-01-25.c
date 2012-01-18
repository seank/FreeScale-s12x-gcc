#include <string.h>

char foo[10];

int main()
{
  memset (foo, 1, sizeof (foo));
  return foo[0] - 1;
}
