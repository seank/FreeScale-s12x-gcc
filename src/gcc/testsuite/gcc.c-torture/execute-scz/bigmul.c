long a = 10000;
long b = 200000;
unsigned long c = 100000;
unsigned long d = 20000;
long long e = 100000000LL;
long long f = 200000000LL;

int main()
{
  long r;
  unsigned long p;
  long long q;
  
  r = a * b;
  if (r != 10000 * 200000)
    return 1;

  p = c * d;
  if (p != 100000 * 20000)
    return 1;

  q = e * f;
  if (q != 100000000LL * 200000000LL)
    return 1;
  
  return 0;
}

  
