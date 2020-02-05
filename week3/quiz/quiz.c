#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

int main(int argc, char** argv)
{
	for(double x=1; x<2.005; x = x+0.01){
		printf("%lf\t%lf\n", x, 1./sqrt(x));

	}
	return 0;
}

