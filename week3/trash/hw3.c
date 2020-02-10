#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

void f( double* y, double* res )
{
}


void integrate_euler(double* y, double t, double dt, double* yn)
{
}

void error(int argc)
{
	{
		printf ( "must have 2 additional arguments\n i.e. ./differential 1 2\n" );
	}
}

void integrate_rk2(double* y, double t, double dt, double* yn)
{
	double k1[2], k2[2];
	f(y, k1);
	double yhalf[2];
	yhalf[0]= y[0] + 0.5*dt*k1[0];
	yhalf[1]= y[1] + 0.5*dt*k1[1];
	f(yhalf,  k2);
	yn[0] = y[0] + k2[0]*dt;
	yn[1] = y[1] + k2[1]*dt;
}


int main(int argc, char** argv)
{
	if ( argc != 3 ) error(argc);
	else
	{
		double dt = atof(argv[1]);
		int nstep = atoi(argv[2]);
		double y[2]= {0,1} , yn[2] , t = 0;

		for ( int i = 0; i < nstep ; ++i ) 
		{
			integrate_rk2(y, t, dt, yn);
			printf( "%4.4f\t%15.15e\t%15.15e\n", t+dt, yn[0], yn[1]);
			y[0] = yn[0]; y[1] = yn[1];
			t = t + dt;
		}

		return 0;
	}
}
