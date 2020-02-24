#include	<stdlib.h>

void integrate_rk2(long double* y, int n, long double t, long double dt, long double* yn, long double* mass, void (*f)(long double*, long double, long double*, long double*))
{
	long double *k1 = malloc(n*sizeof(long double));
	long double *k2 = malloc(n*sizeof(long double));

	f(y, t, k1, mass);

	long double *yhalf = malloc(n*sizeof(long double));
	for(int k = 0; k <n; k++) yhalf[k]= y[k] + 0.5*dt*k1[k];

	f(yhalf, t + 0.5*dt, k2, mass);

	for(int k = 0; k < n; k++) yn[k] = y[k] + k2[k]*dt;

	free(yhalf);
	free(k1);
	free(k2);
}
