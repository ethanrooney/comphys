#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sk(int n, int k)
{

	double sum = 0;
	for(int i = 1; i <=n; i++)
	{
		sum += 1.0/pow(i,k);
	}
	return sum;

}

double logsum(int n)
{
	
	double sum = 0;
	for(int i = 1; i <= n; i++)
	{
		sum += 1./i - log10(n);
	}
	return sum;

}

void printline(int n)
{
		printf("%i %lf %lf %lf %lf\n", n, logsum(n), sk(n,2), sk(n,3), sk(n,4));
}

int main(int argc, char** argv)
{
	for(int n = 1; n<=100; n++)
	{
		printline(n);
	}
	printf("\n");
}
