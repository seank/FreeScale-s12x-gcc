/* Handle GEL page0 indications.  The global/static variables
   specified with that attribute will be put within page0.  */
#define PAGE0_ATTRIBUTE __attribute__((section(".page0")))

char var PAGE0_ATTRIBUTE;

int main()
{
  var |= 1;
  if (var & 2)
    var &= 8;
  return 0;
}
