typedef short bsdstuff_size_t;
char *strncpy(char *dst, const char *src, bsdstuff_size_t n)
{
  // printf("src=%s\r\n", src);
  // printf("size=%d", n);
  if (n != 0) {
    char *d = dst;
    const char *s = src;
    
    do {
      if ((*d++ = *s++) == 0) {
        /* NUL pad the remaining n-1 bytes */
        while (--n != 0)
          *d++ = 0;
        break;
      }
    } while (--n != 0);
  }
  //printf("dst=%s\r\n", dst);
  
  return (dst);
  
}

static const char* strings[] = {
  "hello world",
  "a",
  "bb",
  "0123456789012234568",
  "asfasfsgdhtrhwrthrhwvdvegqeasdfasf",
  0
};

int
main ()
{
  char buf[64];
  char *p;
  int i;

  for (i = 0; strings[i] != 0; i++)
    {
      memset (buf, 1, sizeof (buf));
      if (buf[3] != 1 || buf[12] != 1 || buf[sizeof (buf) - 1] != 1)
        abort ();

      p = strncpy (buf, strings[i], sizeof (buf));
      if (buf[sizeof (buf) - 1] != 0)
        abort ();
      if (p != buf)
        abort ();

      if (buf[0] != strings[i][0])
        abort ();
      if (strcmp (buf, strings[i]) != 0)
        abort ();
    }
  return 0;
}
