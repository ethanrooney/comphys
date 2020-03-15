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

void printmat(double* mat, int n)// prints a matrix "mat" with size n*n
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

void swaprow( double* mat, int n, int r1, int r2)// when called will change the positions of 2 rows 
{
	for(int c=0; c<n; ++c) swap(mat+r1*n+c, mat+r2*n+c);
}

void gauss_elim(double* a, int n, double *b) // Preforms Gauss elimination to a triangular a matrix
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
		swap(b+i, b+imax);

		for(int r=i+1; r<n; ++r)
		{
			double rat = a[r*n+i] / a[i*n+i];
			for( int c=i; c<n; ++c) a[r*n+c] -= rat*a[i*n+c];
			b[r] -= rat*b[i];
		}
	}
}

void bks(double* a, int n, double* b, double* x) // Triangular matrix will solve
{
	for(int j=n-1; j>=0; --j)
	{
		double temp = b[j];
		for(int k=j+1; k<n; ++k) temp -= a[j*n+k]*x[k];
		x[j] = temp/a[j*n+j];
	}
}

void solvemat(double* a, int n, double* b, double* x) // solves a matrix when called
{
	gauss_elim(a, n, b);
	bks(a, n, b, x);
}

double req(double* r, int nr, int* l1, int* l2, int nv, int vin, int vout)
/*
{
	double I = 1.0;
	int n=nr+nv-1;

	double* m = (double*)malloc(n*n*sizeof(double));
	double* b = (double*)malloc(n*sizeof(double));
	double* x = (double*)malloc(n*sizeof(double));

	for(int i=0; i<n*n; ++i) m[i] = 0;

	for(int i=0; i<n; ++i) b[i] = 0;

	for(int k =0; k<nr; ++k)
	{ 
		m[k*n+l1[k]] = 1.0;
		m[k*n+l2[k]] = -1.0;
		m[k*n+nv+k] = -r[k];
	}
	printmat(m,n);

	for(int j=0; j<nr; ++j)
	{ 
		int row = nr+l1[j];
		if(row != n-1) m[row*n+nv+j] = -1.0;
		row = nr+l2[j];
		if(row != n-1) m[row*n+nv+j] = 1.0;
	}
	printmat(m,n);
	


	m[(n-1)*n] = 1.0; // What is goin on in here?
	printmat(m,n);

	if(nr+vin != n-1) b[nr+vin] = -I;
	if(nr+vout != n-1) b[nr+vout] = I;
	printmat(m,n);


	solvemat(m, n, b, x);
	printmat(m,n);

	double dv = x[vin] - x[vout];

	free(x);
	free(b);
	free(m);
	return dv;
}
*/

{
	int neq=nr+nv-1;

	double* m = (double*)malloc(neq*neq*sizeof(double));
	double* b = (double*)malloc(neq*sizeof(double));
	double* x = (double*)malloc(neq*sizeof(double));

	for(int i=0; i<neq*neq; ++i) m[i] = 0;

	for(int i = 0; i<nr; ++i)
	{ 
		int v = l1[i];
		if( v < nv-1 ) m[(nr+v)*neq +i] = 1;
		v = l2[i];
		if( v < nv-1 ) m[(nr+v)*neq +i] = -1;
	}

	for(int i=0; i<nv-1; ++i) b[nr+i] =0;
	if(vin != neq-1) b[nr+vin] = +1;
	if(vout != neq-1) b[nr+vout] = -1;

	for(int i=0; i<nr; ++i)
	{ 
		m[i*neq + i] = -r[i];
		int v = l1[i];
		if(v < nv-1) m[i*neq +nr + v] = 1;
		v = l2[i];
		if(v < nv-1) m[i*neq +nr + v] = -1;
		b[i] = 0;
	}
	solvemat(m, neq, b, x);

	double vbeg = (vin<nv-1)? x[nr+vin] : 0; // WTF does this do
	double vend = (vout<nv-1)? x[nr+vout] : 0;


	free(x);
	free(b);
	free(m);
	return vbeg - vend;
}



int main(int argc, char** argv)
/*
{
	double rt[] = {1,2,3,4,5};
	int l1t[] = {0,1,2,0,1};
	int l2t[] = {1,2,3,3,3};

	double rest = req(rt, 5, l1t, l2t, 4, 0, 2);

	printf ("rest: %e\n", rest);

}
*/

{
	int in_i = atoi(argv[2]);
	int in_j = atoi(argv[3]);
	int out_i = atoi(argv[4]);
	int out_j = atoi(argv[5]);
	int n = atoi(argv[1]);
	int nr = n*(n-1)*2;
	int nv = (n)*(n);
	
	int nrt = nr + 2*n;

	double r[nrt];
	for(int i=0; i<nrt; ++i)
		r[i] = 1;

	int* l1 = (int*)malloc(nrt*sizeof(int));
	int* l2 = (int*)malloc(nrt*sizeof(int));

	for(int i = 0; i<n-1; i++)
	{
		for(int j = 0; j<n; j++)
		{
			l1[i+(n-1)*j] = i+(n)*j;
			l2[i+(n-1)*j] = i+(n)*j+1;
		}
	}

	for(int i = 0; i<n; i++)
	{
		for(int j = 0; j<n-1; j++)
		{
			l1[i+(n)*j+nr/2] = i+(n)*j;
			l2[i+(n)*j+nr/2] = i+(n)*j+n;
		}
	}

	for(int i = 0; i<n; i++)
	{
		int j = n-1;
		l1[nr+n+i]=i+(n)*j;
		l2[nr+n+i]=i;
	}

	for(int j = 0; j<n; j++)
	{
		int i = n-1;
		l1[nr+j]=i+(n)*j;
		l2[nr+j]=n*j;
	}

//	printf("r:  "); for(int i=0; i<nr; i++) printf("%lf ", r[i]); printf("\n");
//	printf("l1: "); for(int i=0; i<nr; i++) printf("%i ", l1[i]); printf("\n");
//	printf("l2: "); for(int i=0; i<nr; i++) printf("%i ", l2[i]); printf("\n");

	double res = req(r, nrt, l1, l2, nv, in_i+n*in_j, out_i + n*out_j);

	printf("%lf\n", res);
	return 0;
}
