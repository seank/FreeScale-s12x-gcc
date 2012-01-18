signed char value;

signed char values[] = {
  0,  1,  2,  3,  5,  7, 9, 16, 127, 128
};

signed char expect[] = {
 12, 13, 14, 15, 13, 15, 13, 28, 127, 140
};

void
orqi_global ()
{
  value |= 12;
}

void
orqi_ptr (signed char* p)
{
  *p |= 12;
}

signed char
orqi_return (signed char v)
{
  return v | 12;
}

int
main()
{
  unsigned i;
  signed char c;
  
  for (i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
      value = values[i];
      orqi_global ();
      if (value != expect[i])
        abort ();

      c = values[i];
      orqi_ptr (&c);
      if (c != expect[i])
        abort ();

      c = orqi_return (values[i]);
      if (c != expect[i])
        abort ();
    }
  exit (0);
}
