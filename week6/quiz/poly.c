/*
 * =====================================================================================
 *
 *       Filename:  poly.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/11/2020 02:30:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ethan Rooney (), ethan.f.rooney@protonmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

typedef struct { double x, y, sigma; } dpoint;

double poly(double* a, int m, double x)
{
	double res = 0;
	for(int k=0; k<m+1; ++k) res += a[k]*pow(x,k);

	return res;
}

double chisq(double* a, int m, dpoint* data, int n)
{
	double res = 0;
	for(int i = 0; i<n; ++i)
	{
		res += pow((data[i].y - poly(a, m, data[i].x))/data[i].sigma, 2);
	}
	return(res);
}

void generate_data(dpoint* data, int n)
{
	for(int x=1, x<n+1, ++x)
	{
		data[x-1].x = x;
		data[x-1].y = 1+2*x+3*x*x;
		data[x-1].x = drand48();

	}
}

int main(int argc, char** argv)
{

	dpoint data[] = {1,1,1, 2,2,1, 3,4,1, 4,3,1, 5,4.5,0.2};
	double a[] = {0,1};
	

	double res = chisq(a, 1, data, 5);

	printf("%lf\n", res);

	return 0;
}

