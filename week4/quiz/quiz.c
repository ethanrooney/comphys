#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

int jose (int n)
{
	int res = 0;
	for( int i=1 ; i<=n ; ++i) res += i;
	return res;
}
	/* -----  end of function test  ----- */
int main(int argc, char** argv)
{
	int n = 100;
	for (int i= 1; i<=n; i++){
	printf("%i\t%i\n" ,i,jose(i));
	}
	return 0;
}

