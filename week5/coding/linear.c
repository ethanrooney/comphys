/*
 * =====================================================================================
 *
 *       Filename:  linear.c
 *
 *    Description:  Generic Linear Algebra Solver for nxn matrix
 *
 *        Version:  1.0
 *        Created:  02/24/2020 03:05:46 PM
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

void printmat(double* mat, int n)
{
	for(int r= 0; r<n; ++r)
	{
		for(int c = 0; c<n; ++c) printf("% 5.2f ", mat[r*n+c]);
		printf("\n");
	}
	printf("\n");
}

void swap(double* a, double* b) // swap the values of 2 values
{
	double tmp = *a;			// Gives us a temporary place in memory to hold  *a
		*a = *b;
		*b = tmp;
}

void swaprow( double* mat, int n, int r1, int r2)
{
	for(int c=0; c<n; ++c) swap(mat+r1*n+c, mat+r2*n+c);
}

void gauss_elim(double* a, int n, double *b)
{
	for(int i=0; i<n; ++i)
	{
		int imax = i; double max = fabs(a[i*n+i]);
		for(int k = i+i; k<n; ++k)
		{
			if(fabs(a[k*n+i]) >max)
				{
					max = fabs(a[k*n+i]); 
					imax = k;
				}
		}
		swaprow(a, n, i, imax);

		for(int r=i+1; r<n; ++r)
		{
			double rat = a[r*n+i] / a[i*n+i];
			for( int c=i; c<n; ++c) a[r*n+c] -= rat*a[i*n+c];
			b[r] -= rat*b[i];
		}
	}
}

int main(int argc, char** argv)
{
	double mat[] = {1,1,1,1,2,2,2,3,4};
	double b[] = {3,5,9};
	printmat(mat,3);
	gauss_elim(mat, 3, b);
	printmat(mat,3);
	return 0;
}

