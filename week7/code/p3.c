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

typedef struct { double a, b, c, xsqr; } four_point;

double gausrnd()
{
  srand48(time(NULL)+clock());
  double u1 = drand48();
  double u2 = drand48();
  return sqrt(-2*log(u1))*cos(2*M_PI*u2);
}

void file_data(FILE *df, dpoint* data, double* sum_y, double* sum_ysqr, int array_len, int num_array)
{
	for(int i=0; i<array_len*num_array;i++)
	{
		fscanf(df, "%lf %lf %lf", &data[i].x, &data[i].y, &data[i].sigma);
	}
}

void boot_array(dpoint* bs_data, dpoint* act_data, int array_len, int num_array, double* sum_y, double* sum_ysqr)
{
	for(int i = 0; i < array_len; i++)
	{
		bs_data[i].x = act_data[i].x;
		bs_data[i].y = act_data[i].y+act_data[i].sigma*gausrnd();
		bs_data[i].sigma=act_data[i].sigma;
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

void chi_fit(int M, dpoint *data, int N, int j, four_point* poly_fits)
{
	double* a = (double*)malloc((M+1)*(M+1)*sizeof(double));
	double* b = (double*)malloc((M+1)*sizeof(double));
	double* alpha = (double*)malloc((M+1)*sizeof(double));

    computeab(data, N, a, M, b);
    solve_linsys(a, M+1, b, alpha);
	poly_fits[j].a=alpha[0];
	poly_fits[j].b=alpha[1];
	poly_fits[j].c=alpha[2];
	poly_fits[j].xsqr=chisq(alpha, M, data, N);

    printf("%lf\n", poly_fits[j].c);

	free(a);
	free(b);
	free(alpha);
}

void get_stats(four_point* y, int N)
{
	double sum_a=0, sumsq_a=0;
	double sum_b=0, sumsq_b=0;
	double sum_c=0, sumsq_c=0;
	double sum_xsqr=0, sumsq_xsqr=0;
	double av_a, std_a;
	double av_b, std_b;
	double av_c, std_c;
	double av_xsqr, std_xsqr;
	for(int i=0; i<N; i++)
	{
		sum_a += y[i].a; sumsq_a += y[i].a*y[i].a;
		sum_b += y[i].b; sumsq_b += y[i].b*y[i].b;
		sum_c += y[i].c; sumsq_c += y[i].c*y[i].c;
		sum_xsqr += y[i].xsqr; sumsq_xsqr += y[i].xsqr*y[i].xsqr;
	}
	av_a = sum_a/N; sumsq_a /= N; std_a = sqrt(sumsq_a - (av_a)*(av_a)); printf("%lf\t%lf\t", av_a, std_a);
	av_b = sum_b/N; sumsq_b /= N; std_b = sqrt(sumsq_b - (av_b)*(av_b)); printf("%lf\t%lf\t", av_b, std_b);
	av_c = sum_c/N; sumsq_c /= N; std_c = sqrt(sumsq_c - (av_c)*(av_c)); printf("%lf\t%lf\t", av_c, std_c);
	av_xsqr = sum_xsqr/N; sumsq_xsqr /= N; std_xsqr = sqrt(sumsq_xsqr - (av_xsqr)*(av_xsqr)); printf("%lf\t%lf\n", av_xsqr, std_xsqr);
}

int main(int argc, char** argv)
{
	FILE* df = fopen(argv[1], "r");// Opens file given by the first argument
	int array_len = 13;//The Number of data points taken by each student
	int num_array =1 ;//The number of student data sets taken
	int N = atoi(argv[2]);

	dpoint* exp_data=(dpoint*)malloc(array_len*num_array*sizeof(dpoint));//Will use this to store the data provided experimentally
	dpoint* bs_data =(dpoint*)malloc(array_len*sizeof(dpoint));// Will use this to store the bootstrap of the data sample
	double* sum_y = (double*)malloc(array_len*sizeof(double));// Used for calculating the Sigma
	double* sum_ysqr = (double*)malloc(array_len*sizeof(double));// ^^

	four_point* poly_fits = (four_point*)malloc(N*sizeof(four_point));


	file_data(df, exp_data, sum_y, sum_ysqr, array_len, num_array);

	for(int j=0; j<N; j++) 
	{
		boot_array(bs_data, exp_data, array_len, num_array, sum_y, sum_ysqr);
		chi_fit(2, bs_data, array_len, j, poly_fits);
	}

	free(sum_ysqr);
	free(sum_y);
	free(bs_data);
	free(exp_data);
	fclose(df);
	return 0;
}

