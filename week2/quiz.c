#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argv, char** args)
{
	double n = atof(args[1]);
	printf("%lf\n", n*n);
	return 0;
}
