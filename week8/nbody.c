#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integrator.c"

int NBODY;
double mass=1;
double eps=1;
double r0=1;

double force(double r)
{
  return 24*eps*(2*pow(r0/r,12)-pow(r0/r,6))/r;
}

void F(double* y, double t, double* res)
{
  
  for(int i=0; i<2*NBODY; ++i) res[i] = y[2*NBODY+i];

  for(int i=0; i<NBODY; ++i)
  {
    res[2*NBODY+2*i] = 0;   // vx_i
    res[2*NBODY+2*i+1] = 0; // vy_i
    for(int j=0; j<NBODY; ++j) if(j!=i)
    {
      double r[2] = { y[2*j] - y[2*i], y[2*j+1]-y[2*i+1] };
      double magr = sqrt(r[0]*r[0]+r[1]*r[1]);
      double f = force(magr);
      res[2*NBODY+2*i]   += -(f/mass)*r[0]/magr;      
      res[2*NBODY+2*i+1] += -(f/mass)*r[1]/magr;
    }
  } 
}

void init_positions(double* y, double L)
{
  int nside = ceil(sqrt(NBODY));

  double step = pow(2,1.0/6)*r0;
  if(step*nside > L) step = L/nside;

  for(int i=0, n=0; i<nside; ++i)
  for(int j=0; (j<nside) && (n<NBODY); ++j, ++n)
  {
    y[2*n+0] = i * step;
    y[2*n+1] = j * step;
  }

}

double pot(double r)
{
  return 4*eps*(pow(r0/r,12) - pow(r0/r,6));
}

double compute_pot(double* y)
{
  double res = 0;
  for(int i=0; i<NBODY; ++i)
  for(int j=i+1; j<NBODY; ++j)
  {
    double r[2] = {y[2*i+0]-y[2*j+0], y[2*i+1]-y[2*j+1]};
    double dist = hypot(r[0], r[1]);
    res += pot(dist);
  }
  return res;
}

void init_velocities(double* y, double EperN)
{
  double U = compute_pot(y);
  double KperN = EperN - U/NBODY;

  if(KperN<0)
  {
    printf("Cannot find a good initial configuration ... exiting\n");
    abort();
  }

  double vel = sqrt(2*KperN/mass);

  for(int i=0; i<NBODY; ++i)
  {
    double ang = drand48()*2*M_PI;
    y[2*NBODY+2*i+0] = vel*cos(ang);
    y[2*NBODY+2*i+1] = vel*sin(ang);
  }
}

int main(int argc, char** argv)
{
  if(argc < 6)
  {
    printf("Usage: %s N L EperN deltat t nskip\n", argv[0]);
    return -1;
  }
  NBODY = atoi(argv[1]);
  double L = atof(argv[2]);
  double EperN = atof(argv[3]);
  double dt = atof(argv[4]);
  double T  = atof(argv[5]);
  int nstep = ceil(T/dt);
  int nskip = atoi(argv[6]);
  

  double *y, *yn, t=0;
  y = malloc(NBODY*4*sizeof(double));
  yn = malloc(NBODY*4*sizeof(double));

  init_positions(y, L);
  init_velocities(y, EperN);

  for(int i=0; i<nstep; ++i)
  {
    integrate_rk2(y, 4*NBODY, t, dt, yn, F);
    if((i+1)%nskip == 0)
    {
      printf("% .5f ", t+dt);
      for(int k=0; k<4*NBODY; ++k) printf("%20.15e ", yn[k]);
      printf("\n");
    }
    for(int k=0; k<4*NBODY; ++k) y[k] = yn[k];
    t = t + dt;
  } 
 
  free(y);
  free(yn);
  return 0;
}
