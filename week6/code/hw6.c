#include "linalg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//double drand48(void);

typedef struct { double x, y, sigma; } dpoint;

void computeab(dpoint* data, int N, double* a, int M, double* b)
{
  for(int r=0; r<M+1; ++r)
  {
    b[r] = 0;
    for(int i=0; i<N; ++i) 
      b[r] += data[i].y*pow(data[i].x,r)/pow(data[i].sigma,2);
    for(int c=0; c<M+1; ++c)
    {
       a[r*(M+1)+c] = 0;
       for(int i=0; i<N; ++i)
         a[r*(M+1)+c] += pow(data[i].x,r+c)/pow(data[i].sigma,2);
    }
  }
}

double gausrnd()
{
  double u1 = drand48();
  double u2 = drand48();
  return sqrt(-2*log(u1))*cos(2*M_PI*u2);
}

void  generate_data(dpoint* data, int N)
{
  for(int x=1; x<N+1; ++x)
  {
    data[x-1].x = x;
    data[x-1].sigma = 0.5;
    data[x-1].y = 1+2*x+3*x*x + data[x-1].sigma*gausrnd();
  }
}

double poly(double* alpha, int M, double x)
{
  double res = 0;
  for(int k=0; k<M+1; ++k) res += alpha[k]*pow(x,k);
  return res;
}


double chisq(double* alpha, int M, dpoint* data, int N)
{
  double res=0;
  for(int i=0; i<N; ++i)  
    res += pow( (data[i].y-poly(alpha, M, data[i].x))/data[i].sigma,2);
  return res;
}

int numlines(FILE* df)
{

	char c;
	int N=0;
	for(c=getc(df); c != EOF; c = getc(df)) if(c== '\n') N+=1;

	return(N);
}


int main(int argc, char** argv)
{
	
	int N;
	FILE *df;
	df = fopen(argv[1], "r");

	N=numlines(df);
	printf("%i\n", N);
	rewind(df);

	dpoint *data = (dpoint*)malloc(N*sizeof(dpoint));

	double x, y, sigma;
	for(int i = 0; fscanf(df, "%lf %lf %lf", &x, &y, &sigma)!=EOF; i++)
	{
		data[i].x=x, data[i].y=y, data[i].sigma=sigma;
	}
	fclose(df);

	int M = 2;
	double* a = (double*)malloc((M+1)*(M+1)*sizeof(double));
	double* b = (double*)malloc((M+1)*sizeof(double));
	double* alpha = (double*)malloc((M+1)*sizeof(double));

    computeab(data, N, a, M, b);
    solve_linsys(a, M+1, b, alpha);

    printf("%lf ", chisq(alpha, M, data, N));
    printf("\n");

	free(a);
	free(b);
	free(alpha);
	free(data);

	return 0;
}
