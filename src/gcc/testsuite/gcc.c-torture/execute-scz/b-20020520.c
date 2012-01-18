 static  struct {
     unsigned int b0 : 1;
   int v : 4;
   int b : 8;
  }tester;

int main()
{
  tester.b = 4;
  tester.v = 2;
  return tester.b0;
}

