#include <stdio.h>

int main(int argc, char** argv)
{
	printf("Temperture in Celcius: ");
	double tc;
	scanf("%lf", &tc);
	double tf = 32+tc*(9./5);
	printf("Tc: % 10.2f\n", tf);
	return 0;
}

