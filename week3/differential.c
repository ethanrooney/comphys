#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

void f( double y, double t, double* res )
{
	*res = -y;
}

void integrate(double y, double t, double dt, double* yn){
	double k;
	f(y, t, &k);
	*yn = y + k*dt;
}


int main(int argc, char** argv)
{

	if ( argc != 3 ) {
		printf ( "must have 2 additional arguments\n i.e. ./differential 1 2\n" );
		return -1;
	}
		double dt = atof(argv[1]);
		int nstep = atoi(argv[2]);

		double y = 1 , yn = 0, t = 0;

		for ( int i = 0; i < nstep ; ++i ) {
			integrate(y, t, dt, &yn);
			printf( "%4.4f\t%15.15e\n", t+dt, yn);
			y = yn;
			t = t + dt;
		}
		return 0;
}
