/*
 * =====================================================================================
 *
 *       Filename:  quiz.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/10/2020 01:05:12 PM
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  test
 *  Description:  
 * =====================================================================================
 */
int
test ()
{
	return 1;
}		/* -----  end of function test  ----- */
int main(int argc, char** argv)
{
	for ( int i = 0; i <10 ; i++ ) {
		printf("%i\n" , test());
	}
}

