unsigned long addsi_shift(unsigned long* a, unsigned long* b)
{
  *a = (*b << 16) + *a;
  return *a;
}

