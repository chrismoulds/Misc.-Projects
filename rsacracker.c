/* 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>

struct gcdstruct{
	
	long top[100];
	long middle[100];
	long bottom[100];
	};

struct rowpointers{

	long *t1; 
	long *t2;
	long *m;
	long *b1;
	long *b2;
	long *b3;
	long size;
	};

/*
* 
* RSA "Cracking" Algorithm (With known p and q values)
*
* Compile with gcc -o rsa rsacracker.c 
* Run with ./rsa -p -q -e where p and q are your prime numbers and e is your
* public encryption value.
*
* Author: Chris Moulds
*
*/

void gcd(long phi_f, long e, struct gcdstruct *gcds, 
	struct rowpointers *rps)
{

	long temp; 

	rps->t1 = gcds->top;
	rps->t2 = gcds->top;
	rps->m = gcds->middle;
	rps->b1 = gcds->bottom;
	rps->b2 = gcds->bottom;
	rps->b3 = gcds->bottom;
	rps->size = 0;

	*(rps->t1) = phi_f;
	rps->t2++;
	*(rps->t2) = e;
	
		
	printf("Calculating GCD(e, phi_f)...\n");

	while ( *(rps->t2) != 0 ){
		 
		*(rps->m)=(*(rps->t1))/(*(rps->t2));
		temp = *(rps->t2);
		rps->t2++;
		*(rps->t2) = (*(rps->t1))%temp;
		rps->t1++;
		rps->m++; 
		rps->size++;
	}

	if (*(rps->t1) != 1){
		printf("Invalid p, q or e value(s). GCD(e, phi_f) != 1.\n");
		printf("Exiting.\n");
		printf("\n");
		exit(1);
	}
	
	else printf("GCD = 1 ... OK.\n");


}

void crack_d(long phi_f, struct gcdstruct *gcds, struct rowpointers *rps)
{

	long temp = 0;	
	rps->m--;
	rps->m--;
	*(rps->b1) = 0;
	rps->b1++;
	*(rps->b1) = 1;
	rps->b1++;
	rps->b2++;
	
	for (int i=0; i<(rps->size)-1; i++){

		*(rps->b1) = ( (*(rps->m)) * (*(rps->b2)) ) + *(rps->b3);

		rps->m--;
		rps->b1++;
		rps->b2++;
		rps->b3++;
		temp++;

	}

	if (temp%2){
		*(rps->b2) = -(*(rps->b2));
		*(rps->b2) += phi_f;
	}

	printf("The decryption value is: %ld\n", *(rps->b2));
	printf("\n");

}
	


static void usage()
{
	printf("usage: enter values p q e\n");
	exit(1);
}


int main(int argc, char * argv[])
{
	long p, q, e, phi_f;
	struct gcdstruct gcds;
	struct rowpointers rps;

	if (argc != 4)
		usage();

	p = strtoul(argv[1], NULL, 0);
	q = strtoul(argv[2], NULL, 0);
	e = strtoul(argv[3], NULL, 0);

	phi_f = (p-1)*(q-1);

	printf("\n------RSA-DECRYPT-LITE------\n");
	printf("Cracking d for N=%ld and e=%ld\n", p*q, e);
	printf("Euler's Totient = %ld\n", phi_f);

	gcd(phi_f, e, &gcds, &rps);
	
	crack_d(phi_f, &gcds, &rps);

	return 0;
}
