#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double gaussrnd()
{
  double u1 = drand48();
  double u2 = drand48();
  return sqrt(-2*log(u1))*cos(2*M_PI*u2);
}

int main(int argc, char** argv)
{
  srand48(time(NULL)+clock());
  for(int i = 0; i<100000;i++) 
  {
    printf("%20.15lf\t%20.15lf\n", drand48(), gaussrnd());
  }
  return 0;
}
