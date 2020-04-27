void shift.plusx(int nphi, double* phi, double* psi, int* ne)
{
	for(int i = 0; i < nphi; i++)
	{
		psi[i] = phi[ne[i*4+1]];
	}
}

void shift.plusx(int nphi, double* phi, double* psi, int* ne)
{
	for(int i = 0; i< nphi; i++)
	{
		for(int j=0; j<=4; i++)
		{
			psi[i] += phi[ne[i*4+j]] - 4*psi[i];
		}
	}
}

void print_grad(int nphi, double* phi, double* pos, int* ne, double a)
{
	double grad =  malloc(double*nphi*2)
	for(int i = 0; i<nphi; i++)
	{
		grad[i*2] = 0.5(phi[ne[i*4+2]] - phi[ne[i*4+1]])/a;
		grad[i*2+1] = 0.5(phi[ne[i*4+4]] - phi[ne[i*4+3]])/a;
		printf("%lf\t%lf\t%lf\t%lf", pos[i*2], pos[i*2+1], grad[i*2], grad[i*2+1])
	}
	free(grad);
}
