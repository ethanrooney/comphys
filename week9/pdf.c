#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double getrnd()
{
  return drand48();
}

int main(int argc, char** argv)
{
  int N = atoi(argv[1]);
  for(int i=0; i<N; ++i) printf("%e\n", getrnd());
  return 0;
}
