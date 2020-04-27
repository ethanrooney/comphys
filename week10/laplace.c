#include <stdio.h>
#include <stdlib.h>

type struct
{
  int index;
  double x,y;
  int ne[4];
} point;

void setup(int N, int *nphi, int *ne, double *pos)
{
  point* p = malloc(N*N*sizeof(point));

  double a = 3.0/(N-1);

  for(int i=0; i<N; ++i)
  for(int j=0; j<N; ++j)
  {
    int idx = i*N+j;
    p[idx].index = i*N+j;
    p[idx].x = j*a-1.5;
    p[idx].y = i*a-1.5;
    p[idx].ne[0] = i*N+j+1;
    p[idx].ne[1] = i*N+j-1;
    p[idx].ne[2] = (i+1)*N+j;
    p[idx].ne[3] = (i-1)*N+j;
  }

  free(p);
}

void gauss_seidel(int nphi, double* phi, int *ne, double delta)
{
  for(;;)
  {
    double err=0, nrm=0;
    for(int i=0; i<nphi; ++i)
    { 
      double tmp = (phi[ ne[4*i+0] ]+ phi[ ne[4*i+1] ] + phi[ ne[4*i+2] ]
              + phi[ ne[4*i+3] ])/4;
      err += (tmp - phi[i])*(tmp-phi[i]);
      nrm += tmp*tmp;
    }
    if( sqrt(err/nrm) < delta) break;
  }
}

int main(int argc, char** argv)
{
  int N = atoi(argv[1]);
  double delta = atof(argv[2]);

  int* ne = malloc(4*N*N*sizeof(int));
  double* pos = malloc(2*N*N*sizeof(double));

  int nphi;
  setup(N, &nphi, ne, pos);

  double* phi = malloc((nphi+2)*sizeof(double));
  phi[0] = 0;
  phi[1] = 100;

  gauss_seidel(nphi, phi+2, ne, delta);

  free(ne);
  return 0;
}
