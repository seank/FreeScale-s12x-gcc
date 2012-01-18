unsigned long lsqrt (unsigned long x)
{
	if (x <= 1)
		return x;

	/* If 'x' is small enough, use 16-bit integers.  */
	if ((x & 0xFFFF0000L) == 0)
	{
		unsigned short v0, x0, q0, x1;

		v0 = (unsigned short) (x);
		x0 = v0 / 2;
		while (1)
		{
			q0 = v0 / x0;
			x1 = (x0 + q0) / 2;
			if (q0 >= x0)
				break;
			x0 = x1;
		}
		return (unsigned long) x1;
	}
	else
	{
		unsigned long v0, q0, x1;

		v0 = x;
		x = x / 2;
		while (1)
		{
			q0 = v0 / x;
			x1 = (x + q0) / 2;
			if (q0 >= x)
				break;
			x = x1;
		}
		return x1;
	}
}

int main ()
{
  unsigned long result = lsqrt (40);
  if (result != 6)
    exit (1);

  return 0;
}


