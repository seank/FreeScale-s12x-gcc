struct a 
{
  int a;
  int b;
  char bar[253];
  long d;
  int c[3];
};

struct a table[10];

int get(int p)
{
  return table[p].c[2];
}
