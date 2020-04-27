/*
 * =====================================================================================
 *
 *       Filename:  ratio.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/23/2020 03:03:39 PM
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

double gaussrnd()
{
  double u1 = drand48();
  double u2 = drand48();
  return sqrt(-2*log(u1))*cos(2*M_PI*u2);
}


int main(int argc, char** argv)
{
	double x0 = atof(argv[1]);
	double sigmax = atof(argv[2]);
	double y0 = atof(argv[3]);
	double sigmay = atof(argv[4]);
	int N = atoi(argv[5]);



	for(int i=0; i<N; ++i)
	{
		double x = x0 + sigmax*gaussrnd();
		double y = y0 + sigmay*gaussrnd();
		printf("%.20lf\n", log(x*x+y*y));
	}



	return 0;
}

