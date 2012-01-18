struct bfield 
{
  int b1 : 1;
  int b2 : 2;
  int b3 : 3;
  int b4 : 4;
  int b5 : 5;
  int b6 : 6;
  int b7 : 7;
  int b8 : 8;
  int b9 : 9;
  int b10: 10;
  int b11: 11;
  int b12: 12;
  int b13: 13;
  int b14: 14;
  int b15: 15;
};

struct bfield
fillup (int value)
{
  struct bfield bf;

  bf.b1 = value;
  bf.b2 = value;
  bf.b3 = value;
  bf.b4 = value;
  bf.b5 = value;
  bf.b6 = value;
  bf.b7 = value;
  bf.b8 = value;
  bf.b9 = value;
  bf.b10 = value;
  bf.b11 = value;
  bf.b12 = value;
  bf.b13 = value;
  bf.b14 = value;
  bf.b15 = value;
  return bf;
}

int
compare (struct bfield b1, struct bfield b2)
{
  if (b1.b1 != b2.b1)
    return 1;
  if (b1.b2 != b2.b2)
    return 2;
  if (b1.b3 != b2.b3)
    return 3;
  if (b1.b4 != b2.b4)
    return 4;
  if (b1.b5 != b2.b5)
    return 5;
  if (b1.b6 != b2.b6)
    return 6;
  if (b1.b7 != b2.b7)
    return 7;
  if (b1.b8 != b2.b8)
    return 8;
  if (b1.b9 != b2.b9)
    return 9;
  if (b1.b10 != b2.b10)
    return 10;
  if (b1.b11 != b2.b11)
    return 11;
  if (b1.b12 != b2.b12)
    return 12;
  if (b1.b13 != b2.b13)
    return 13;
  if (b1.b14 != b2.b14)
    return 14;
  if (b1.b15 != b2.b15)
    return 15;

  return 0;
}

int
expect_value (int n, int bits)
{
  if (n & (1 << (bits - 1)))
    return (n & ((1 << bits) - 1)) | ~((1 << bits) - 1);
  else
    return (n & ((1 << bits) - 1));
}


int
main ()
{
  long long n;
  long i, j;
  unsigned cnt_char, cnt_short, cnt_long, cnt_longlong;
  struct bfield b1, b2;
  
  for (i = 0; i < 32768; )
    {
      int res;

      b1 = fillup (i);
      b2 = fillup (i);
#define exit(P) {printf ("At %d\n", __LINE__); return 1; }

      if (b1.b1 != expect_value (i, 1))
	exit (1);
      if (b1.b2 != expect_value (i, 2))
	exit (1);
      if (b1.b3 != expect_value (i, 3))
	exit (1);
      if (b1.b4 != expect_value (i, 4))
	exit (1);
      if (b1.b5 != expect_value (i, 5))
	exit (1);
      if (b1.b6 != expect_value (i, 6))
	exit (1);
      if (b1.b7 != expect_value (i, 7))
	exit (1);
      if (b1.b8 != expect_value (i, 8))
	exit (1);
      if (b1.b9 != expect_value (i, 9))
	exit (1);
      if (b1.b10 != expect_value (i, 10))
	exit (1);
      if (b1.b11 != expect_value (i, 11))
	exit (1);
      if (b1.b12 != expect_value (i, 12))
	exit (1);
      if (b1.b13 != expect_value (i, 13))
	exit (1);
      if (b1.b14 != expect_value (i, 14))
	exit (1);

      if (b1.b15 != expect_value (i, 15))
	exit (1);

      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B1 */
      b2.b1 = ~b2.b1;
      res = compare (b1, b2);
      if (res != 1)
	exit (1);

      b2.b1 = b1.b1;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);
      
      /* B2 */
      b2.b2 = ~b2.b2;
      res = compare (b1, b2);
      if (res != 2)
	exit (1);

      b2.b2 = b1.b2;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);
      
      /* B3 */
      b2.b3 = ~b2.b3;
      res = compare (b1, b2);
      if (res != 3)
	exit (1);

      b2.b3 = b1.b3;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);
      
      /* B4 */
      b2.b4 = ~b2.b4;
      res = compare (b1, b2);
      if (res != 4)
	exit (1);

      b2.b4 = b1.b4;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);
      
      /* B5 */
      b2.b5 = ~b2.b5;
      res = compare (b1, b2);
      if (res != 5)
	exit (1);

      b2.b5 = b1.b5;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B6 */
      b2.b6 = ~b2.b6;
      res = compare (b1, b2);
      if (res != 6)
	exit (1);

      b2.b6 = b1.b6;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B7 */
      b2.b7 = ~b2.b7;
      res = compare (b1, b2);
      if (res != 7)
	exit (1);

      b2.b7 = b1.b7;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B8 */
      b2.b8 = ~b2.b8;
      res = compare (b1, b2);
      if (res != 8)
	exit (1);

      b2.b8 = b1.b8;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B9 */
      b2.b9 = ~b2.b9;
      res = compare (b1, b2);
      if (res != 9)
	exit (1);

      b2.b9 = b1.b9;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B10 */
      b2.b10 = ~b2.b10;
      res = compare (b1, b2);
      if (res != 10)
	exit (1);

      b2.b10 = b1.b10;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B10 */
      b2.b10 = ~b2.b10;
      res = compare (b1, b2);
      if (res != 10)
	exit (1);

      b2.b10 = b1.b10;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B11 */
      b2.b11 = ~b2.b11;
      res = compare (b1, b2);
      if (res != 11)
	exit (1);

      b2.b11 = b1.b11;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B12 */
      b2.b12 = ~b2.b12;
      res = compare (b1, b2);
      if (res != 12)
	exit (1);

      b2.b12 = b1.b12;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B13 */
      b2.b13 = ~b2.b13;
      res = compare (b1, b2);
      if (res != 13)
	exit (1);

      b2.b13 = b1.b13;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B14 */
      b2.b14 = ~b2.b14;
      res = compare (b1, b2);
      if (res != 14)
	exit (1);

      b2.b14 = b1.b14;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      /* B15 */
      b2.b15 = ~b2.b15;
      res = compare (b1, b2);
      if (res != 15)
	exit (1);

      b2.b15 = b1.b15;
      res = compare (b1, b2);
      if (res != 0)
	exit (1);

      if (i < 300)
        {
          i++;
        }
      else
        {
          i += 119;
        }
    }
  return 0;
}
