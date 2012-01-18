extern __attribute__((noreturn)) void bar(char*, int);

void get(int size, char c)
{
  char *buf[size];
  bar (buf, size);
}
