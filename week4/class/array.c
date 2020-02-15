/*
 * =====================================================================================
 *
 *       Filename:  array.c
 *
 *    Description:  Array
 *
 *        Version:  1.0
 *        Created:  02/10/2020 02:40:35 PM
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

void initarray(double* y)
{
	printf("inside1: %p\n", y);
	y[0] = 1;
	y[1] = 2;
	y[2] = 3;
	y[3] = 4;

	double a; y = &a;
	printf("inside2: %p\n", y);
}

int main(int argc, char** argv)
{
	double y[4];

	printf("outsid1: %p\n", y);
	initarray(y);
	printf("outsid2: %p\n", y);

	for(int k=0; k<4 ; ++k)
		printf("%e ", y[k]);
	printf("\n");
	return 0;
}

