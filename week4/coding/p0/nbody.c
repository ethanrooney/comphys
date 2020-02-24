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

void F( long double* y, long double t, long double* res, long double* mass )
{
	for(int i=0; i<2*NBODY; ++i) res[i] = y[2*NBODY+i];
	
	for(int i=0; i<NBODY; ++i)
	{
		res[2*NBODY+2*i]	= 0;		// vxi is equal to the initial vxi
		res[2*NBODY+2*i+1]	= 0;		// vyi is equal to the initial vyi
		for(int j=0; j<NBODY; ++j) if(j!=i)
		{
			long double r[2] = { y[2*j] - y[2*i], y[2*j+1]-y[2*i+1] };
			long double magr = sqrt(r[0]*r[0]+r[1]*r[1]);
			res[2*NBODY+2*i]	+= G*mass[j]*r[0]/pow(magr,3);	//vxi
			res[2*NBODY+2*i+1]	+= G*mass[j]*r[1]/pow(magr,3);	//vyi
		}
	}
}

int main(int argc, char** argv)
{
	long double	dt		= atof(argv[1]);
	long double	tmax	= atof(argv[2]);
	long double	m0		= atof(argv[3]);
	long double	x0		= atof(argv[4]);
	long double	y0		= atof(argv[5]);
	long double	vx0		= atof(argv[6]);
	long double	vy0		= atof(argv[7]);
	long double	m1		= atof(argv[8]);
	long double	x1		= atof(argv[9]);
	long double	y1		= atof(argv[10]);
	long double	vx1		= atof(argv[11]);
	long double	vy1		= atof(argv[12]);
	long double	m2		= atof(argv[13]);
	long double	x2		= atof(argv[14]);
	long double	y2		= atof(argv[15]);
	long double	vx2		= atof(argv[16]);
	long double	vy2		= atof(argv[17]);

	long double mass[NBODY] = {m0,m1,m2};

	long double y[4*NBODY] = {x0,y0,x1,y1,x2,y2,vx0,vy0,vx1,vy1,vx2,vy2}, yn[4*NBODY], t=0;

	for (int i=0; i*dt<tmax-0.5*dt; ++i)
	{
		integrate_rk2(y,4*NBODY, t, dt, yn, mass, F);
		printf("%4.4Lf ", t+dt);
		for ( int k=0; k<4*NBODY; k++) printf("%15.30Lf ", yn[k]);
		printf("\n");
		for(int k=0; k<4*NBODY; ++k) y[k] = yn[k];
		t = t + dt;
	}
	return 0;
}
