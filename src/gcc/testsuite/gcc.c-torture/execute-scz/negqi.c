signed char value;

signed char values[] = {
  0, 1, 2, 3, 5, 7, 9, 16, 127, 128
};

signed char expect[] = {
  0, -1, -2, -3, -5, -7, -9, -16, -127, 128
};

void
negqi_global ()
{
  value = - value;
}

void
negqi_ptr (signed char* p)
{
  *p = - *p;
}

signed char
negqi_return (signed char v)
{
  return -v;
}

int
main()
{
  unsigned i;
  signed char c;
  
  for (i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
      value = values[i];
      negqi_global ();
      if (value != expect[i])
        abort ();

      negqi_global ();
      if (value != values[i])
        abort ();

      c = value;
      negqi_ptr (&c);
      if (c != expect[i])
        abort ();

      negqi_ptr (&c);
      if (c != values[i])
        abort ();

      c = negqi_return (c);
      if (c != expect[i])
        abort ();

      c = negqi_return (c);
      if (c != values[i])
        abort ();
    }
  exit (0);
}
