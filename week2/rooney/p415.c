#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double PI =		3.1415926535897932385;
double exact =	1.7182818284590452353;
double x_0 = M_PI/6;

double f(double x, double x_0)
{
	double g = 9.81;
	double L = 1;
	return 1./(sqrt(2*(g/L)*(cos(x)-cos(x_0))));
}

double integrateleft(double a, double b, long int N)
{
	double delx = (b - a)/N;
	double res = 0;

	for(int i=0; i<N; i++)
	{
		res += delx*f(a+delx*i, x_0); //you don't need to put in {} if it is a single line statment
	}

	return res;
}
double integratemiddle(double a, double b, long long int N)
{
	double delx = (b - a)/N;
	double res = 0;

	for(long long int i=0; i<N; i++)
	{
		res += delx*f(a+delx*i+0.5*delx, x_0); //you don't need to put in {} if it is a single line statment
	}

	return res;
}

int main(int argv, char** args)
{
	if(argv < 4)
	{
		double resMiddle = integratemiddle(-x_0, x_0, atoi(args[1]));
		printf("%15.15lf\n", resMiddle);
	}
	else
	{
		printf("You must provide an integer number between 1 and 2147483647\n");
		return -1;
	}
	return 0;
}
