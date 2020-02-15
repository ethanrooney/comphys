#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

#define NBODY 2

double mass[NBODY] = {1,1};

const double G = 4*M_PI*M_PI; // AU^3 * YEAR^-2 SOL^-1

void f( double* vect, double t, double* res )
{
	res[0] = vect[2]; //dv_x/dt = a_x
	res[1] = vect[3]; //dv_y/dt = a_y
	res[2] = -vect[0]*vect[1]*vect[1]; //dx/dt = v_x
	res[3] = -vect[0]*vect[0]*vect[1]; //dx/dt = v_x
}

int main(int argc, char** argv)
{
	double dt = atof(argv[1]);
	int nstep = atoi(argv[2]);

	double y[4*NBODY] = {0,0,1,0,0,0,0,1}, yn[4*NBODY], t=0;

	for (int i=0; i<nstep; ++i)
	{
		integrate_rk2(y,4*NBODY, t, dt, yn, F);
		// the following function prints of time, v_x, v_y, x, y, orbital energy, radius, potential energy, kinetic energy
		printf( "%10.9f %15.15f %15.15f %15.15f %15.15f\n", t+dt, y[0], y[1], y[2], y[3]);
		for(int k=0; k<4*NBODY; ++k) y[k] = yn[k];
		t = t + dt;
	}
	return 0;
}
