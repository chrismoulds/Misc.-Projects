/*
* Project Euler Problem #9:
* 
* A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
* a^2 + b^2 = c^2
* For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
*
* There exists exactly one Pythagorean triplet for which a + b + c = 1000.
* Find the product abc.
* 
* Author: Chris Moulds
*/


#include <stdio.h>

int main()
{
	int a, b, c, sum;
	 
	for (int i = 1; i < 500; i++){
		for (int j = 1; j < 500; j++){
			sum = 1000*i + 1000*j - (i*j);
			if (sum == 500000){
				a = i;
				b = j;
				goto calc;
			}
		}
	}

	calc:
		c = 1000 - a - b;
		c *= (a*b);
		printf("abc: %d\n", c);

	return 0;
}
