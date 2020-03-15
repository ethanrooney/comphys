#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(double* a, double* b)
{
  double c = *a;
  *a = *b;
  *b = c;
}

void swap_rows(double* m, int N, int r1, int r2)
{
  for(int c = 0; c < N; ++c) swap(m + r1*N + c, m + r2*N + c);
}

int find_pivot(double* m, int N, int r)
{
  int p = r;
  double val = fabs(m[r*N + r]);
  for(int rp = r + 1; rp < N; ++rp)
    if(fabs(m[rp*N + r]) > val)
    {
      p = rp;
      val = fabs(m[rp*N + r]);
    }
  return p;
}

void elimination(double* m, int N, double* b)
{
  for(int r = 0; r < N - 1; ++r)
  {
    int p = find_pivot(m, N, r);
    if(p != r)
    {
      swap_rows(m, N, r, p);
      swap(b + r, b + p);
    }

    double piv = m[r*N + r];
    if(fabs(piv) < 1e-20)
    {
      printf("Matrix nearly singular. Exiting ... \n");
      abort();
    }

    for(int rp = r + 1; rp < N; ++rp)
    {
      double fact = -m[rp*N + r]/piv;
      for(int c = r; c < N; ++c) m[rp*N + c] += fact*m[r*N + c];
      b[rp] += fact*b[r];
    }
  }
}

void bks(double* m, int N, double* b, double* x)
{
  for(int r = N - 1; r > -1; --r)
  {
    double temp = b[r];
    for(int c = r + 1; c < N; ++c) temp -= m[r*N + c]*x[c];
    x[r] = temp/m[r*N + r];
  }
}

void solve_system(double* m, int N, double* b, double* x)
{
  elimination(m, N, b);
  bks(m, N, b, x);
}

	
void printmat(double* mat, int n)// prints a matrix "mat" with size n*n
{
	for(int r= 0; r<n; ++r)
	{
		for(int c = 0; c<n; ++c) printf("% 5.2f ", mat[r*n+c]);
		printf("\n");
	}
	printf("\n");
}

struct resistor
{
  int v1, v2;
  double R;
};

double compute_resistance(int nv, int nr, struct resistor* lr, int beg, int end)
{
  int neq = nr + nv - 1;

  double *m = (double*)malloc(neq*neq*sizeof(double));
  double *b = (double*)malloc(neq*sizeof(double));
  double *x = (double*)malloc(neq*sizeof(double));

  for(int i = 0; i < neq*neq; ++i) m[i] = 0;

  for(int i = 0; i < nr; ++i)
  {
    int v = lr[i].v1;
    if(v < nv - 1) m[(nr + v)*neq + i] = +1;
    v = lr[i].v2;
    if(v < nv - 1) m[(nr + v)*neq + i] = -1;
  }

  for(int i = 0; i < nv - 1; ++i) b[nr + i] = 0;
  if(beg < nv - 1) b[nr + beg] = +1;
  if(end < nv - 1) b[nr + end] = -1;

  for(int i = 0; i < nr; ++i)
  {
    m[i*neq + i] = -lr[i].R;
    int v = lr[i].v1;
    if(v < nv - 1) m[i*neq + nr + v] = +1;
    v = lr[i].v2;
    if(v < nv - 1) m[i*neq + nr + v] = -1;
    b[i] = 0;
  }

  printmat(m, neq);
  solve_system(m, neq, b, x);
  printmat(m, neq);
  double vbeg = (beg < nv - 1)? x[nr + beg] : 0;
  double vend = (end < nv - 1)? x[nr + end] : 0;

  free(b);
  free(x);
  free(m);

  return vbeg - vend;
}

double do_grid(int n, int in_i, int in_j, int out_i, int out_j)
{
  struct resistor* lr = (struct resistor*)malloc(2*n*n*sizeof(struct resistor));

  for(int i=0; i < n; ++i)
  {
    for(int j = 0; j < n; ++j)
    {
      lr[i*n + j].R = 1;
      lr[i*n + j].v1 = i*n + j;
      lr[i*n + j].v2 = i*n + (j+1)%n;

      lr[i*n + j + n*n].R = 1;
      lr[i*n + j + n*n].v1 = n*i + j;
      lr[i*n + j + n*n].v2 = ((i + 1)%n)*n + j;
    }
  }

  double res = compute_resistance(n*n, 2*n*n, lr, n*in_i + in_j, n*out_i + out_j);
  free(lr);

  return res;
}

int main(int argc, char** argv)
{
  int n     = atoi(argv[1]);
  int in_i  = atoi(argv[2]);
  int in_j  = atoi(argv[3]);
  int out_i = atoi(argv[4]);
  int out_j = atoi(argv[5]);

  double res = do_grid(n, in_i, in_j, out_i, out_j);
  printf("Resistance: %f \n", res);

  return 0;
}


