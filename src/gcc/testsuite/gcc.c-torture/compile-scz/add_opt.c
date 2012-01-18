unsigned long addsi_and16(unsigned long a, unsigned long b)
{
  return a + (b & 0x0ffff);
}

unsigned long addsi_zext(unsigned long* a, unsigned long* b)
{
  *a = *a + (*b & 0x0ffff);
  return *a;
}

unsigned long addsi_shift(unsigned long* a, unsigned long* b)
{
  *a = *a + (*b << 16);
  return *a;
}

