static unsigned char spi_test1[256];

void fnTest(void)
{
  unsigned short i;
   
  for (i = 0; i < sizeof(spi_test1); i++) 
    {
      spi_test1[i] = (unsigned char)i;
    }
}

void main(void)
{
  fnTest ();
  
  if (spi_test1[0] != 0)
    exit (1);

  if (spi_test1[1] != 1)
    exit (2);

  if (spi_test1[10] != 10)
    exit (3);

  exit (0);
}
