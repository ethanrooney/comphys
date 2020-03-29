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
#include	"linalg.c"
#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>
#include	<time.h>
typedef struct { double x, y, sigma; } dpoint;

void file_head(FILE *df, int* array_len, int* num_array)
{
	fscanf(df, "%i %i", num_array, array_len);
}

void file_data(FILE *df, dpoint* data, double* sum_y, double* sum_ysqr, int array_len, int num_array)
{
	for(int i=0; i<array_len; i++)
	{
		sum_y[i]=0;
		sum_ysqr[i]=0;
	}
	for(int i=0; i<array_len*num_array;i++)
	{
		fscanf(df, "%lf %lf", &data[i].x, &data[i].y);
		//printf("%lf %lf\n", data[i].x, data[i].y);
		sum_y[i%array_len] += data[i].y;
		sum_ysqr[i%array_len] += data[i].y*data[i].y;
	}
}

void boot_array(dpoint* bs_data, dpoint* act_data, int array_len, int num_array, double* sum_y, double* sum_ysqr)
{
	srand48(time(NULL)+clock());
	int N;
	for(int i = 0; i < array_len; i++)
	{
		N = floor(drand48()*num_array);
		bs_data[i].x=act_data[N*array_len+i].x;
		bs_data[i].y=act_data[N*array_len+i].y;
		bs_data[i].sigma = sqrt(  sum_ysqr[i]/num_array - pow(sum_y[i]/num_array,2));
		//printf("%lf %lf %lf\n",bs_data[i].x, bs_data[i].y, bs_data[i].sigma);
	}
}

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
	FILE* df = fopen(argv[1], "r");
	int array_len;
	int num_array;
	file_head(df, &array_len, &num_array);
	
	dpoint* exp_data=(dpoint*)malloc(array_len*num_array*sizeof(dpoint));
	dpoint* bs_data =(dpoint*)malloc(array_len*sizeof(dpoint));
	double* sum_y = (double*)malloc(array_len*sizeof(double));
	double* sum_ysqr = (double*)malloc(array_len*sizeof(double));


	file_data(df, exp_data, sum_y, sum_ysqr, array_len, num_array);
	

	for(int i=0; i<=atoi(argv[2]); i++) 
	{
		boot_array(bs_data, exp_data, array_len, num_array, sum_y, sum_ysqr);
		chi_fit(2, bs_data, array_len);
	}
	
	



	fclose(df);
	return 0;
}

