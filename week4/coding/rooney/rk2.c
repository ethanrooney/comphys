#include	<stdlib.h>

void integrate_rk2(double* y, int n, double t, double dt, double* yn, double* mass, void (*f)(double*, double, double*, double*))
{
	double *k1 = malloc(n*sizeof(double));
	double *k2 = malloc(n*sizeof(double));

	f(y, t, k1, mass);

	double *yhalf = malloc(n*sizeof(double));
	for(int k = 0; k <n; k++) yhalf[k]= y[k] + 0.5*dt*k1[k];

	f(yhalf, t + 0.5*dt, k2, mass);

	for(int k = 0; k < n; k++) yn[k] = y[k] + k2[k]*dt;

	free(yhalf);
	free(k1);
	free(k2);
}
