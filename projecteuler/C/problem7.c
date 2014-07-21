/*
* Project Euler Problem #7:
*
* What is the 10001st prime number? 
* 
* Author: Chris Moulds
*/

#include <stdio.h>
#include <math.h>

int is_prime(int i)
{
if (i < 2)
        return 0;
    else if (i == 2)
        return 1;
    for (long j = 2; j <= pow(i, 0.5); j++){ 
    	if (i % j == 0)
        	return 0;
    }
    	
    return 1;
}

int main()
{
	int counter = 0;
	int prime = 2;

	while (1){
		if (is_prime(prime))
			counter++;
		if (counter == 10001)
			break;
		prime++;		
	}
		
	printf("10001st PRIME: %d\n", prime);

	return 0;
}
