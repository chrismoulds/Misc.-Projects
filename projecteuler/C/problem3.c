/*
* Project Euler Problem #3:
* The prime factors of 13195 are 5, 7, 13 and 29.
*
* What is the largest prime factor of the number 600851475143 ?
* 
* Author: Chris Moulds
*/


#include <stdio.h>
#include <math.h>

int is_prime(long i)
{
	if (i<2)
        return 0;
    else if (i == 2)
        return 1;
    for (long j=2; j<=pow(i, 0.5); j++){ 
    	if (i%j == 0)
        	return 0;
    }
    return 1;
}

int main()
{
	long number = 600851475143;
	long testnumber = 0;
	int j = 2;
	while (1){
		testnumber = number/j;
		if (number%testnumber == 0){
			if (is_prime(testnumber))
				break;
		}
		j++;
	}
		
	printf("LARGEST PRIME FACTOR: %ld\n", testnumber);

	return 0;
}