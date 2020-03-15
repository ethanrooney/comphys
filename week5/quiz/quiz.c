/*
 * =====================================================================================
 *
 *       Filename:  quiz.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/26/2020 02:30:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ethan Rooney (), ethan.f.rooney@protonmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

double lognfact(int n)
{
	double res =0;
	for(int i = 1; i<=n; i++)
	{
		res = res+log(i);
	}
	return res;
}
	

int main(int argc, char** argv)
{
	for(int i = 1; i<=100; i++)
	{
		printf("%i\t%lf\n",i,lognfact(i));
	}
	return 0;
}

