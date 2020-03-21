#include <stdio.h>

int main(int argc, char** argv)
{
	printf("%12s %12s\n", "Celcius", "Farhenheit");
	for(double tc = 0; tc < 101; tc = tc + 5) // declairing a variable inside of the loop minimizes the scope of a variable it will be undeclared when the loop ends
	{
		double tf = 32+tc*(9./5);
		printf("% 12.2f %12.2f\n", tc, tf);
	}
	return 0;
}
