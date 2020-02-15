#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

const double GM = 4*M_PI*M_PI; // AU^3 * YEAR^-2

void f( double* vect, double t, double* res )
{
	res[0] = vect[2]; //dv_x/dt = a_x
	res[1] = vect[3]; //dv_y/dt = a_y
	res[2] = -vect[0]*vect[1]*vect[1]; //dx/dt = v_x
	res[3] = -vect[0]*vect[0]*vect[1]; //dx/dt = v_x
}


void integrate_rk2(double* y, double t, double dt, double* yn)
{
	double k1[4], k2[4];
	double yhalf[4];

	f(y, t, k1);
	for(int k = 0; k <4; ++k) yhalf[k]= y[k] + 0.5*dt*k1[k];

	f(yhalf, t + 0.5*dt, k2);
	for(int k = 0; k < 4; ++k) yn[k] = y[k] + k2[k]*dt;
}

int main(int argc, char** argv)
{
	double dt = atof(argv[1]);
	int nstep = atoi(argv[2]);

	double x_0 = 0;
	double y_0 = 0;
	double v_x = 1;
	double v_y = 2;

	double y[4] = {x_0, y_0, v_x, v_y}, yn[4], t=0;

	for (int i=0; i<nstep; ++i)
	{
		integrate_rk2(y, t, dt, yn);
		// the following function prints of time, v_x, v_y, x, y, orbital energy, radius, potential energy, kinetic energy
		printf( "%10.9f %15.15f %15.15f %15.15f %15.15f\n", t+dt, y[0], y[1], y[2], y[3]);
		for(int k=0; k<4; ++k) y[k] = yn[k];
		t = t + dt;
	}

	return 0;

}
