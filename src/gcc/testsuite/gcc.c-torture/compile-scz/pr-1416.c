
#define MIN(x1,x2) (x1 > x2)?x1:x2
typedef unsigned short WORD;

WORD wT;
WORD TstMin(void) {
  return MIN(wT, 99);
}
