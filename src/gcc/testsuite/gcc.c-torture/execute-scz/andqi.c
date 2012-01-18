signed char value;

signed char values[] = {
  0, 1, 2, 3, 5, 7, 9, 16, 127, 128
};

signed char expect[] = {
  0, 0, 0, 0, 4, 4, 8, 0, 12, 0
};

void
andqi_global ()
{
  value &= 12;
}

void
andqi_ptr (signed char* p)
{
  *p &= 12;
}

signed char
andqi_return (signed char v)
{
  return v & 12;
}

int
main()
{
  unsigned i;
  signed char c;
  
  for (i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
      value = values[i];
      andqi_global ();
      if (value != expect[i])
        abort ();

      c = values[i];
      andqi_ptr (&c);
      if (c != expect[i])
        abort ();

      c = andqi_return (values[i]);
      if (c != expect[i])
        abort ();
    }
  exit (0);
}
