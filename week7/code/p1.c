/*
 * =====================================================================================
 *
 *       Filename:  hw7.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/26/2020 06:28:44 PM
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
#include	<time.h>

double gausrnd()
{
  double u1 = drand48();
  double u2 = drand48();
  return sqrt(-2*log(u1))*cos(2*M_PI*u2);
}


int main(int argv, char** argc)
{
	srand48(time(NULL)+clock());
	for(int i = 0; i < atoi(argc[1]); i++)
	{
		printf("%20.20lf\t%20.20lf\n",drand48(), gausrnd());
	}
}

