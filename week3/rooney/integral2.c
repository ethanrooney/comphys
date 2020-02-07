#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

const double GM = 4*M_PI*M_PI; // AU^3 * YEAR 
const double a  = 4*M_PI*M_PI;

void f( double* vect, double* res )
{
	res[0] = -GM*vect[2]/pow(vect[2]*vect[2]+vect[3]*vect[3], 1.5); //dv_x/dt = a_x
	res[1] = -GM*vect[3]/pow(vect[2]*vect[2]+vect[3]*vect[3], 1.5); //dv_y/dt = a_y
	res[2] = vect[0]; //dx/dt = v_x
	res[3] = vect[1]; //dv/dt = v_y
}


void integrate_rk2(double* y, double dt, double* yn){
	double k1[4], k2[4];
	double yhalf[4];

	f(y, k1);

	yhalf[0]= y[0] + 0.5*dt*k1[0];
	yhalf[1]= y[1] + 0.5*dt*k1[1];
	yhalf[2]= y[2] + 0.5*dt*k1[2];
	yhalf[3]= y[3] + 0.5*dt*k1[3];

	f(yhalf, k2);

	yn[0] = y[0] + k2[0]*dt;
	yn[1] = y[1] + k2[1]*dt;
	yn[2] = y[2] + k2[2]*dt;
	yn[3] = y[3] + k2[3]*dt;
}


int main(int argc, char** argv)
{

		double dt = atof(argv[1]);
		int nstep = atoi(argv[2]);

		double y[4]= {0 ,2*M_PI, 1, 0} , yn[4] , t = 0;

		for ( int i = 0; i < nstep ; ++i ) {
			integrate_rk2(y, dt, yn);
			printf( "%4.4f\t%f\t%f\t%f\t%f\t%f\n", t+dt, y[0], y[1], y[2], y[3], pow(y[2]*y[2]+y[3]*y[3], 0.5));
			y[0] = yn[0];
			y[1] = yn[1];
			y[2] = yn[2];
			y[3] = yn[3];
			t = t + dt;
		}
		return 0;
}
