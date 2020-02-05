#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double PI =		3.1415926535897932385;
double exact =	1.7182818284590452353;

double f(double x)
{
	return exp(x);
}

double integrateleft(double a, double b, long int N)
{
	double delx = (b - a)/N;
	double res = 0;
	double x = 0;
	for(int i=0; i<N; i++)
	{
		x = delx*i;
		printf("%e\t%e\n", x, res);
		res += delx*f(a+delx*i); //you don't need to put in {} if it is a single line statment
	}

	return res;
}
double integratemiddle(double a, double b, long long int N)
{
	double delx = (b - a)/N;
	double res = 0;
	double x = 0;

	for(long long int i=0; i<N; i++)
	{
		x = delx*i;
		printf("%e\t%e\n", x, res);
		res += delx*f(a+delx*i+0.5*delx); //you don't need to put in {} if it is a single line statment
	}

	return res;
}

int main(int argv, char** args)
{
	if(argv < 4)
	{
		if(strncmp(args[1], "-m", 2)){
			integratemiddle(0, 1, atoi(args[2]));
		}
		if(strncmp(args[1], "-l", 2)){
			integrateleft(0,1, atoi(args[2]));
		}
		printf("%c", strncmp(args[1], "-m",2));
	}
	else
	{
		printf("You must provide an integer number between 1 and 2147483647\n");
		return -1;
	}
	return 0;
}
