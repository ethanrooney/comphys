#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double GM = 4*M_PI*M_PI // AU^3*YEAR^-2

void F(	double y1, double y2, double y3, double y4, 
		double t, 
		double *res1, double* res2, double* res3, double* res4)

{

  *res1 = y2;
  *res2 = -2*y1*y3*y3;
  *res3 = y4;
  *res4 = -2*y1*y1*y3;

}


void integrate_rk2(	double y1old, 
					double y2old,  
					double y3old, 
					double y4old, 
					double t, 
					double dt, 
					double *y1new, 
					double *y2new, 
					double *y3new, 
					double* y4new)
{
  double deriv1, deriv2, deriv3, deriv4;

  F(y1old, y2old, y3old, y4old, 
	t, 
	&deriv1, &deriv2, &deriv3, &deriv4);

  F(y1old+deriv1*dt/2, 
	y2old+deriv2*dt/2, 
	y3old+deriv3*dt/2, 
	y4old+deriv4*dt/2,  
	t+dt/2, 
    &deriv1, 
	&deriv2, 
	&deriv3, 
	&deriv4);

  *y1new = y1old + dt*deriv1;
  *y2new = y2old + dt*deriv2;
  *y3new = y3old + dt*deriv3;
  *y4new = y4old + dt*deriv4;
  
}


void error()
{
	printf("Error: You must provide an argument\n");
}

int main(int argc, char** argv)
{
  if(argc != 2)
  {
	  error();
	  return -1;
  }

  else
  {
	  double y1=0;
	  double y2=1;
	  double y3=0;
	  double y4=2;
	  double t=0;
	  double dt=atof(argv[1]);
	  double tstop = 10;

	  printf("%6.3f  %.15e %.15e %.15e %.15e\n", t, y1, y2, y3, y4);
	  for(; t<tstop-dt/2; t+=dt)

	  {

		double y1new, y2new, y3new, y4new;

		integrate_rk2(	y1, y2, y3, y4, 
						t, dt, 
						&y1new, &y2new, &y3new, &y4new);

		printf(	"%6.3f  %.15e %.15e %.15e %.15e\n", 
				t+dt, y1new, y2new, y3new, y4new);

		y1 = y1new;
		y2 = y2new;
		y3 = y3new;
		y4 = y4new;
	  }
  }

  return 0;

}
