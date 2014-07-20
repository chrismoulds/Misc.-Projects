/*
* Project Euler Problem #5:
* 2520 is the smallest number that can be divided by each of the numbers 
* from 1 to 10 without any remainder.
*
* What is the smallest positive number that is evenly divisible by all of 
* the numbers from 1 to 20?
* 
* Author: Chris Moulds
*/


#include <stdio.h>

int is_divisible(int num)
{
	for (int i = 19; i > 10; i--){
		if (num%i != 0)
			return 0;
	}

	return 1;
}

int main()
{
	int answer = 40;

	while (1){
		if (is_divisible(answer))
			break;
		answer+=20;
	}

	printf("ANSWER: %d\n", answer);

	return 0;
}
