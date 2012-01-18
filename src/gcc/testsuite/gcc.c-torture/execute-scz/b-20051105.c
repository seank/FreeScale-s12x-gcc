struct fields
{
  unsigned long long u1 : 15;
  unsigned long long u2 : 33;
  unsigned long long u3 : 16;
  signed long long   s1 : 15;
  signed long long   s2 : 33;
  signed long long   s3 : 16;
} flags;

struct sfields
{
  unsigned long u1 : 15;
  unsigned long u2 : 17;
  unsigned long u3 : 16;
  signed long    s1 : 15;
  signed long    s2 : 17;
  signed long    s3 : 16;
} sflags;

void break1()
{
}

#define FIELD(S,VAL,CODE) \
  flags.S = VAL;          \
  break1();               \
  if (flags.S != VAL) {   \
    return CODE;          \
  }

#define CHECK_U2(CODE) \
  FIELD(u2,1,CODE+1);        \
  FIELD(u2,2,CODE+1);        \
  FIELD(u2,0x100,CODE+1);     \
  FIELD(u2,0xabcd,CODE+1);    \
  FIELD(u2,0x12ab34cd,CODE+1)

#define CHECK_S2(CODE) \
  FIELD(s2,1,CODE+1);        \
  FIELD(s2,2,CODE+1);        \
  FIELD(s2,0x100,CODE+1);     \
  FIELD(s2,0xabcd,CODE+1);    \
  FIELD(s2,0x12ab34cd,CODE+1)

int main() 
{
  flags.s2 = 1;
  break1();
  if (flags.s2 != 1)
    return 1;

  flags.u2 = 0x1aaaaffffLL;
  break1();
  if (flags.u2 != 0x1aaaaffffLL)
    return 2;
  
  flags.u2 = ~0x1aaaaffffLL;
  break1();
  if (flags.u2 != 0x055550000LL)
    return 3;

  sflags.s2 = 1;
  break1();
  if (sflags.s2 != 1)
    return 4;

  sflags.u2 = 0x1aaffL;
  break1();
  if (sflags.u2 != 0x1aaffL)
    return 5;
  
  sflags.u2 = ~0x1aaffL;
  if (sflags.u2 != 0x5500L)
    return 6;

  CHECK_U2(50);
  return 0;
}
