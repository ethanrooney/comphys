#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>
#include	"rk2.h"


#define NBODY 2
double mass[NBODY] = {1,1};

const double G = 4*M_PI*M_PI; // AU^3 * YEAR^-2 SOL^-1

void F( double* y, double t, double* res )
{
	for(int i=0; i<2*NBODY; ++i) res[i] = y[2*NBODY+i];

	for(int i=0; i<NBODY; ++i)
	{
		res[2*NBODY+2*i] = 0; // vx_i
		res[2*NBODY+2*i+i] = 0; // vy_i
		for(int j=0; j<NBODY; ++j) if(j!=i)
		{
			double r[2] = { y[2*j] - y[2*i], y[2*j+1]-y[2*i+1] };
			double magr = sqrt(r[0]*r[0]+r[1]*r[1]);
			res[2*NBODY+2*i] += G*mass[j]*r[0]/pow(magr,3);
			res[2*NBODY+2*i+1] += G*mass[j]*r[i]/pow(magr,3);
		}
	}
}

int main(int argc, char** argv)
{
	double dt = atof(argv[1]);
	int nstep = atoi(argv[2]);

	double y[4*NBODY] = {0,0,1,0,0,0,0,1}, yn[4*NBODY], t=0;

	for (int i=0; i<nstep; ++i)
	{
		integrate_rk2(y,4*NBODY, t, dt, yn, F);
		printf( "%10.9f %15.15f %15.15f %15.15f %15.15f\n", t+dt, y[0], y[1], y[2], y[3]);
		for ( int k=0; k<4*NBODY; k++) printf("%20.15f ", yn[k]);
		printf("\n");
		for(int k=0; k<4*NBODY; ++k) y[k] = yn[k];
		t = t + dt;
	}
	return 0;
}
