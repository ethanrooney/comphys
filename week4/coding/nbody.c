#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>
#include	"rk2.h"


#define NBODY 3
const double G = 4*M_PI*M_PI; // AU^3 * YEAR^-2 SOL^-1


/* The structure of res[]
 * res[	x0,  y0,  x1,  y1, ...xn-1,  yn-1, 
 *		vx0, vy0, vx1, vx1,...vxn-1, vyn-1
 * Therefore	2*i					= xi
 *				2*i+1				= yi
 *				2*NBODY + 2*i		= vxi
 *				2*NBODY + 2*i + 1	= vyi*/

void F( double* y, double t, double* res, double* mass )
{
	for(int i=0; i<2*NBODY; ++i) res[i] = y[2*NBODY+i];
	
	for(int i=0; i<NBODY; ++i)
	{
		res[2*NBODY+2*i]	= 0;		// vxi is equal to the initial vxi
		res[2*NBODY+2*i+1]	= 0;		// vyi is equal to the initial vyi
		for(int j=0; j<NBODY; ++j) if(j!=i)
		{
			double r[2] = { y[2*j] - y[2*i], y[2*j+1]-y[2*i+1] };
			double magr = sqrt(r[0]*r[0]+r[1]*r[1]);
			res[2*NBODY+2*i]	+= G*mass[j]*r[0]/pow(magr,3);	//vxi
			res[2*NBODY+2*i+1]	+= G*mass[j]*r[1]/pow(magr,3);	//vyi
		}
	}
}

int main(int argc, char** argv)
{
	double	dt		= atof(argv[1]);
	double	tmax	= atoi(argv[2]);
	double	m0		= atoi(argv[3]);
	double	x0		= atoi(argv[4]);
	double	y0		= atoi(argv[5]);
	double	vx0		= atoi(argv[6]);
	double	vy0		= atoi(argv[7]);
	double	m1		= atoi(argv[8]);
	double	x1		= atoi(argv[9]);
	double	y1		= atoi(argv[10]);
	double	vx1		= atoi(argv[11]);
	double	vy1		= atoi(argv[12]);
	double	m2		= atoi(argv[13]);
	double	x2		= atoi(argv[14]);
	double	y2		= atoi(argv[15]);
	double	vx2		= atoi(argv[16]);
	double	vy2		= atoi(argv[17]);

	double mass[NBODY] = {m0,m1,m2};

	double y[4*NBODY] = {x0,y0,x1,y1,x2,y2,vx0,vy0,vx1,vy1,vx2, vy2}, yn[4*NBODY], t=0;

	for (int i=0; i*dt<tmax-0.5*dt; ++i)
	{
		integrate_rk2(y,4*NBODY, t, dt, yn, mass, F);
		printf("%4.4f ", t+dt);
		for ( int k=0; k<4*NBODY; k++) printf("%5.5f ", yn[k]);
		printf("\n");
		for(int k=0; k<4*NBODY; ++k) y[k] = yn[k];
		t = t + dt;
	}
	return 0;
}
