/*
* Project Euler Problem #4:
* A palindromic number reads the same both ways. The largest palindrome made 
* from the product of two 2-digit numbers is 9009 = 91 × 99.
*
* Find the largest palindrome made from the product of two 3-digit numbers.
* 
* Author: Chris Moulds
*/


#include <stdio.h>
#include <stdlib.h>

int is_palindrome(int value)
{
	char *first, *last, string[7];

	sprintf(string, "%d", value);

	first = string;
	last = string;

	while (*last != '\0'){
		last++;
	}
	last--;

	while (last>first){
		if (*first != *last)
			return 0;
		first++;
		last--;
	}

	return 1;
}

int main()
{
	int product = 0;

	while (1){
		for (int i = 999; i > 100; --i){
			for (int j = i; j > 100; --j){
				product = i*j;
				if (is_palindrome(product))
					goto finish;
			}	
		}
	}

	finish:
		printf("LARGEST PALINDROME: %d\n", product);

	return 0;
}
