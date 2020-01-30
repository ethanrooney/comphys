#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

#define PI	3.14159265

double min(double a, double b)
{
	if(a<b)
		return a;
	else
		return b;
}

int main(int argc, char** argv)
{
	if(argc != 8)
	{
		fprintf(stderr,
				"Usage: ./HW1 A_x A_y phi_x phi_y Omega_x Omega_y N\n\n"
				"All arguments should be numbers seperated by a space.\n"
				"Example: ./HW1 3.1 4 2.7 1 7 9.8 100\n\n"
				"See README for more information\n");
		return 1;
	}

	else
	{
		double Ax, Ay, phix, phiy, omegax, omegay, omegamin, wt;

		Ax     = atof(argv[1]);
		Ay     = atof(argv[2]);
		phix   = atof(argv[3]);
		phiy   = atof(argv[4]);
		omegax = atof(argv[5]);
		omegay = atof(argv[6]);
		int n  = atoi(argv[7]);
		char buffer[5000];

		if(omegax == omegay)
		{
			wt = 2*PI;
		}
		else
		{
			wt = 50;
		}

		snprintf(buffer,sizeof(buffer), "cor_%1.0f_%1.0f_%1.0f_%4.2f_%1.0f_%1.0f.txt", Ax, Ay, phix, phiy, omegax, omegay );
		omegamin = min(omegax, omegay);

		double deltat = 2*PI/omegamin/n;

		FILE* data = fopen( buffer , "w");

		for(double t=0; omegamin*t < wt; t += deltat)
		{
			double x = Ax*sin(omegax*t + phix);
			double y = Ay*sin(omegay*t + phiy);
			fprintf(data,"%lf\t%lf\n", x, y);
		}
		fclose(data);
	}
	return 0;
}
