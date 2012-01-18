int check(char *p)
{
  *p = 'a';
  if (*p == 'a')
    return *p;

  return 0;
}
