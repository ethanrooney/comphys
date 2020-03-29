#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printmat(double* mat, int n)
{
  for(int r=0; r<n; ++r)
  {
    for(int c=0; c<n; ++c) printf("% 5.2f  ", mat[r*n+c]);
    printf("\n");
  }
}

void swap(double *a, double* b)
{
  double tmp = *a;
  *a = *b;
  *b = tmp;
}

void swap_rows(double* mat, int n, int r1, int r2)
{
  for(int c=0; c<n; ++c) swap( mat+r1*n+c, mat+r2*n+c);
}

void gauss_elimination(double* a, int n, double* b)
{
  for(int i=0; i<n; ++i)
  {
    int imax = i; double max = fabs(a[i*n+i]);
    for(int k = i+1; k<n; ++k)
    {
      if(fabs(a[k*n+i]) > max) 
      {
        max = fabs(a[k*n+i]);
        imax = k;
      }
    }
    swap_rows(a, n, i, imax);
    // TODO: swap b's too 
    swap(b+i, b+imax);

    for(int r=i+1; r<n; ++r)
    {
      double rat = a[r*n+i] / a[i*n+i];
      for(int c=i; c<n; ++c) a[r*n+c] -= rat*a[i*n+c];
      b[r] -= rat*b[i];
    }
  }
}

void bks(double* a, int n, double* b, double* x)
{
  for(int j=n-1; j >= 0; --j)
  {
    double temp = b[j];
    for(int k=j+1; k<n; ++k) temp -= a[j*n+k]*x[k];
    x[j] = temp/a[j*n+j];
  }
}

void solve_linsys(double* a, int n, double* b, double* x)
{
  gauss_elimination(a, n, b);
  bks(a, n, b, x);
}

