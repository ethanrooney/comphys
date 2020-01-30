#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double PI = 3.1415926535897932385;

double f(double x)
{
	return exp(x);
}

double integrateleft(double a, double b, double N)
{
	double delx = (b - a)/N;
	double res = 0;

	for(int i=0; i<N; i++)
	{
		res += delx*f(a+delx*i); //you don't need to put in {} if it is a single line statment
	}

	return res;
}
double integratemiddle(double a, double b, double N)
{
	double delx = (b - a)/N;
	double res = 0;

	for(long long int i=0; i<N; i++)
	{
		res += delx*f(a+delx*i+0.5*delx); //you don't need to put in {} if it is a single line statment
	}

	return res;
}


int main(int argv, char** args)
{
	double resLeft = integrateleft(0, PI/2, atoi(args[1]));
	double resMiddle = integratemiddle(0, PI/2, atoi(args[1]));
	printf("%15.15lf\t%15.15lf\n",resLeft, resMiddle);
}
