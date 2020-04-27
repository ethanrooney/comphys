#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void compute_stats(double* x, int N, double* av, double* std)
{
  double sum=0, sumsq=0;
  for(int i=0; i<N; ++i) { sum += x[i]; sumsq += x[i]*x[i]; }

  *av = sum/N;
  *std = sqrt( sumsq/N - (*av)*(*av) );
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
