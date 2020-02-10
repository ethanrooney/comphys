#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

const double GM = 4*M_PI*M_PI; // AU^3 * YEAR^-2

void f( double* vect, double* res )
{
	res[0] = -GM*vect[2]/pow(vect[2]*vect[2]+vect[3]*vect[3], 2); //dv_x/dt = a_x
	res[1] = -GM*vect[3]/pow(vect[2]*vect[2]+vect[3]*vect[3], 2); //dv_y/dt = a_y
	res[2] = vect[0]; //dx/dt = v_x
	res[3] = vect[1]; //dv/dt = v_y
}


void integrate_rk2(double* y, double dt, double* yn)
{
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
	if(argc != 6)

	{
		printf("This program takes 5 arguments, inital x, inital v_x, inital v_y, time step, max time.\n");
		return -1;
	}

	double x_0 = atof(argv[1]);
	double v_x = atof(argv[2]);
	double v_y = atof(argv[3]);
	double dt = atof(argv[4]);
	double t_max = atof(argv[5]);
	double y_0 = 0;
	double r = 0 ;
	double v = 0;

	double y[4] = {v_y ,v_x, x_0, y_0};
	double yn[4];

	for ( double t = 0.0; t < t_max+0.5*dt ; t += dt )
	{
		integrate_rk2(y, dt, yn);
		r = pow(y[2]*y[2]+y[3]*y[3], 0.5);
		v = pow(y[0]*y[0]+y[1]*y[1], 0.5);
		//if(fmod(t , 5.0) < dt*1.01)
		{
			// the following function prints of time, v_x, v_y, x, y, orbital energy
			printf( "%10.9f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f\n", t, y[0], y[1], y[2], y[3], 0.5*v*v-GM/r, r, -GM/r, 0.5*v*v);
		}
		y[0] = yn[0];
		y[1] = yn[1];
		y[2] = yn[2];
		y[3] = yn[3];
	}

	return 0;

}
