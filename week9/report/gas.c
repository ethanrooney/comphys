#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int NBODY;
int posacc, posprop, velacc, velprop;
double mass=1;
double eps=1;
double r0=1;

double force(double r)
{
  return 24*eps*(2*pow(r0/r,12)-pow(r0/r,6))/r;
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

void init_velocities(double* y, int nbody, double mass, double kT)
{
  double vel = sqrt(2*kT/mass);
  for(int i=0; i<nbody; ++i)
  {
    double ang = 2*M_PI*drand48();
    y[2*nbody+2*i+0] = vel*sin(ang);
    y[2*nbody+2*i+1] = vel*cos(ang);
  }
}

double compute_pot_one(double* y, int nbody, int j)
{
  double res=0;
  for(int i=0; i<nbody; ++i) if(i!=j)
  {
    double r[2] = {y[2*i+0] - y[2*j+0], y[2*i+1] - y[2*j+1]};
    double d = hypot(r[0], r[1]);
    res += pot(d);
  }
  return res;
}

void update(double* y, double dx, double dv, double kT, double L)
{
  for(int i=0; i<NBODY; ++i)
  {
	velprop++;
    double oldke = (pow(y[2*NBODY+2*i+0],2)+pow(y[2*NBODY+2*i+1],2))*mass/2;
    double nvx = y[2*NBODY+2*i+0] + dv*2*(drand48()-0.5);
    double nvy = y[2*NBODY+2*i+1] + dv*2*(drand48()-0.5);
    double newke = (pow(nvx,2)+pow(nvy,2))*mass/2;
    double r = drand48();
    if( exp(-(newke-oldke)/kT) > r ) //accept
    {
      y[2*NBODY+2*i+0] = nvx;
      y[2*NBODY+2*i+1] = nvy;
	  velacc++;
    }
  }

  for(int i=0; i<NBODY; ++i)
  {
	posprop++;
    double oldpot = compute_pot_one(y, NBODY, i);
    double ox = y[2*i+0];
    double oy = y[2*i+1];
    y[2*i+0] = ox + dx*2*(drand48()-0.5);
    y[2*i+1] = oy + dx*2*(drand48()-0.5);
    if( (y[2*i+0] < 0) || (y[2*i+0] > L) ||
        (y[2*i+1] < 0) || (y[2*i+1] > L) ) // out of box. reject
    {
      y[2*i+0] = ox;
      y[2*i+1] = oy;
      continue;
    }
    double newpot = compute_pot_one(y, NBODY, i);
    double r = drand48();
    if(r > exp(-(newpot-oldpot)/kT)) // reject
    {
      y[2*i+0] = ox;
      y[2*i+1] = oy;
    }
	else posacc++;
  }
}


int main(int argc, char** argv)
{
  if(argc < 6)
  {
    printf("Usage: %s N L kT dx dv nmeas nskip\n", argv[0]);
    return -1;
  }
  NBODY = atoi(argv[1]);
  double L = atof(argv[2]);
  double kT = atof(argv[3]);
  double dx = atof(argv[4]);
  double dv  = atof(argv[5]);
  int nmeas = atoi(argv[6]);
  int nskip = atoi(argv[7]);
  

  double *y;
  y = (double*)malloc(NBODY*4*sizeof(double));

  init_positions(y, L);
  init_velocities(y, NBODY, mass, kT);

  for(int i=0; i<nmeas; ++i)
  {
    for(int j=0; j<nskip; ++j) 
	{
		update(y, dx, dv, kT, L);
	}

    for(int k=0; k<4*NBODY; ++k) printf("%20.15e ", y[k]);

	if(i%(10)==0) fprintf(stderr, "%g\n", ((float) i)/nmeas);
    printf("\n");
  } 


  fprintf(stderr, "kT=%.1lf dx=%.1lf dv=%.1lf\tposacc: %g\tvelacc: %g\n", kT, dx, dv, ((float) posacc)/posprop, ((float) velacc)/velprop);
 
  free(y);
  return 0;
}
