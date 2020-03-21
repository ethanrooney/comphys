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
	rewind(df);

	return(N);
}

void data_from_file(FILE *df, dpoint *data, int N)
{
	double x, y;
	for(int i = 0; fscanf(df, "%lf %lf", &x, &y)!=EOF; i++)
	{
		data[i].x=x, data[i].y=log(y), data[i].sigma=sqrt(y)/y;
		printf("%lf %lf %lf\n", data[i].x, data[i].y, data[i].sigma);
	}
}

void chi_fit(int M, dpoint *data, int N)
{
	double* a = (double*)malloc((M+1)*(M+1)*sizeof(double));
	double* b = (double*)malloc((M+1)*sizeof(double));
	double* alpha = (double*)malloc((M+1)*sizeof(double));

    computeab(data, N, a, M, b);
    solve_linsys(a, M+1, b, alpha);
	for(int i = 0; i<=M; i++) printf("%lf\t", alpha[i]);

    printf("%lf\t", chisq(alpha, M, data, N));
    printf("\n");

	free(a);
	free(b);
	free(alpha);
}


int main(int argc, char** argv)
{
	int M = atoi(argv[2]);
	FILE *df;

	df = fopen(argv[1], "r"); // Opens file given as argument in a read only mode
	int N=numlines(df);       // Gets the number of lines in a file and returns the point to the top of the file

	dpoint *data = (dpoint*)malloc(N*sizeof(dpoint)); // creates a data structure of the proper size

	data_from_file(df, data, N); // Transfers line by line values from df to data.
	chi_fit(M, data, N);         // Fits the function using the fuctions developed by Alexandru

	fclose(df);                  // Properly closes out the file
	free(data);                  // Releases the memory used for data

	return 0;
}
