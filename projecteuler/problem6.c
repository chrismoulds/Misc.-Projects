/*
* Project Euler Problem #6:
* Find the difference between the sum of the squares of the first one 
* hundred natural numbers and the square of the sum.
* 
* Author: Chris Moulds
*/


#include <stdio.h>
#include <math.h>

int gauss_trick(int value){

	return (value*(value + 1))/2;
}

int main()
{
	int difference = 0;
		
	difference = pow(gauss_trick(100), 2);

	for (int i=1; i<=100; i++){
		difference-=pow(i, 2);

	}

	printf("DIFFERENCE: %d\n", difference);

	return 0;
}
