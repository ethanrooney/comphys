#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void compute_stats(double* x, int N, double* av, double* std)
{
  double sum=0, sumsq=0;
  for(int i=0; i<N; ++i) { sum += x[i]; sumsq += x[i]*x[i]; }

  *av = sum/N;
  *std = sqrt( sumsq/N - (*av)*(*av) );
}


double gaussrnd()
{
  double u1 = drand48();
  double u2 = drand48();
  return sqrt(-2*log(u1))*cos(2*M_PI*u2);
}

int main(int argc, char** argv)
{
  int N;
  FILE* f = fopen("data.txt", "r");
  fscanf(f, "%d", &N);
  double* x = malloc(N*sizeof(double));
  for(int i=0; i<N; ++i) fscanf(f, "%lf", &x[i]);
  fclose(f);

  double av, std;
  compute_stats(x, N, &av, &std);

  printf("av: %e   std: %e\n", av, std);

  free(x);
  return 0;

}
