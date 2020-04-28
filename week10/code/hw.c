#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define LENGTH 30.0 //Sets the lenght of one side of a square in cm
#define RADIUS 10.0 //Set the radious of the hole in the middle of the plate

typedef struct
{
  int index;
  double x,y;
  int ne[4];
} point;

void setup(int N, int *nphi, int *ne, double *pos)
{
  point* p = malloc(N*N*sizeof(point));

  double a =  LENGTH /(N-1);

  for(int i=0; i<N; ++i)
  for(int j=0; j<N; ++j)
  {
    int idx = i*N+j;
    p[idx].index = i*N+j;
    p[idx].x = j*a- LENGTH/2.0 ;
    p[idx].y = i*a- LENGTH/2.0 ;
    p[idx].ne[0] = i*N+j+1;
    p[idx].ne[1] = i*N+j-1;
    p[idx].ne[2] = (i+1)*N+j;
    p[idx].ne[3] = (i-1)*N+j;
  }

  double eps = 1e-10;
  for(int i=0; i<N*N; ++i)
  {
    if(fabs(p[i].x)> LENGTH/2.0 -eps) p[i].index = -1;
    if(fabs(p[i].y)> LENGTH/2.0 -eps) p[i].index = -1;
    if(pow(fabs(p[i].x),2) + pow(fabs(p[i].y),2) < RADIUS*RADIUS) p[i].index=-2;
  }

  int newidx=0;
  for(int i=0; i<N*N; ++i) if(p[i].index >= 0) p[i].index=newidx++;
  *nphi = newidx;

  for(int i=0; i<N*N; ++i) if(p[i].index >= 0)
  {
    int idx = p[i].index;
    pos[2*idx+0] = p[i].x;
    pos[2*idx+1] = p[i].y;
    ne[4*idx+0] = p[p[i].ne[0]].index;
    ne[4*idx+1] = p[p[i].ne[1]].index;
    ne[4*idx+2] = p[p[i].ne[2]].index;
    ne[4*idx+3] = p[p[i].ne[3]].index;
  }

  free(p);
}

int gauss_seidel(int nphi, double* phi, int *ne, double delta)
{
  int iter = 0;
  for(;;)
  {
    double err=0, nrm=0;
    for(int i=0; i<nphi; ++i)
    { 
      double tmp = (phi[ ne[4*i+0] ]+ phi[ ne[4*i+1] ] + phi[ ne[4*i+2] ]
              + phi[ ne[4*i+3] ])/4;
      err += (tmp - phi[i])*(tmp-phi[i]);
      nrm += tmp*tmp;
      phi[i] = tmp;
    }
	iter++;
    printf("err: %e nrm: %e\n", sqrt(err), sqrt(nrm));
    if( sqrt(err/nrm) < delta) break;
  }
  return iter;
}

int main(int argc, char** argv)
{
  int iter;
  int N = atoi(argv[1]);
  double delta = atof(argv[2]);

  int* ne = malloc(4*N*N*sizeof(int));
  double* pos = malloc(2*N*N*sizeof(double));

  int nphi;
  setup(N, &nphi, ne, pos);

  printf("nphi: %d\n", nphi);
  for(int i=0; i<nphi; ++i) 
    printf("ne[%d]: %d %d %d %d\n", i, ne[4*i+0], ne[4*i+1], 
      ne[4*i+2], ne[4*i+3]);

  double* phi = malloc((nphi+2)*sizeof(double));
  phi[0] = 0;
  phi[1] = 100;
  for(int i=0; i<nphi; ++i) phi[2+i] = 0;

  iter = gauss_seidel(nphi, phi+2, ne, delta);

  for(int i=0; i<nphi; ++i)
    printf("phi: % +10e  % +10e  % +20e\n", pos[2*i+0], pos[2*i+1],
      phi[2+i]);

  double a =  LENGTH /(N-1);
  for(int i=0; i<nphi; ++i)
  {
    double ex = -(phi[2+ne[4*i+0]] - phi[2+ne[4*i+1]])/(2*a);
    double ey = -(phi[2+ne[4*i+2]] - phi[2+ne[4*i+3]])/(2*a);
    printf("efield: %+10e %+10e  %20e %20e\n", pos[2*i+0], pos[2*i+1],
      ex, ey);
  }

  if(!isatty(fileno(stdout)))
  {
    fprintf(stderr, "Iterations to relaxation time: %i\n",iter);
  }

  free(ne);
  free(pos);
  free(phi); 
  return 0;
}
