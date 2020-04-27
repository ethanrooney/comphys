#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double p(double x)
{
  return exp(-x*x/2);
}

double getrnd()
{
  static double x=10;
  double step = 1.0;
  double xp = x + step*2*(drand48()-0.5); // this is T0

  double r = drand48();

  if(p(xp)/p(x) > r) x = xp;

  return x;
}

int main(int argc, char** argv)
{
  int N = atoi(argv[1]);
  for(int i=0; i<N; ++i) printf("%e\n", getrnd());
  return 0;
}
