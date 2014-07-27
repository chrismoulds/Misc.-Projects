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

/* Used for storing the results of the euclidean algorithm */
struct gcdstruct{
	
	long top[100];
	long middle[100];
	long bottom[100];
	};

/* For manipulating the values in the gcdstruct */
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
* public encryption value. Being that modern RSA keys are normally in the order
* of 1024-2048 bits in length, it is obvious this program is intended for casual
* use with much much smaller numbers. 
*
* EX.) ./rsa 7 11 13 will output d = 37
*
*
* Author: Chris Moulds
*
*/


/*
* gcd()
* Function to verify that the greatest common divisor of e and phi_f = 1
* Perform the Euclidean algorithm while storing the results in the gcds struct
*/
static void gcd(long phi_f, long e, struct gcdstruct *gcds, 
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
		printf("Exiting.\n\n");
		exit(1);
	}
	
	else printf("GCD = 1 ... OK.\n");
}

/*
* crack_d()
* Perform the rest of the algorithm by calculating the linear combination of 
* terms.
*/
static void crack_d(long phi_f, struct gcdstruct *gcds, struct rowpointers *rps)
{
	long temp = 0;	
	rps->m--;
	rps->m--;
	*(rps->b1) = 0;
	rps->b1++;
	*(rps->b1) = 1;
	rps->b1++;
	rps->b2++;
	
	for (int i = 0; i < (rps->size)-1; i++){

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
}

static int validate_d(long e, long phi_f, long *d)
{
	printf("Validating d ... ");
	
	/*
	* Since d is the multiplicative inverse of e modulo phi_f,
	* we can verify it by checking that d*e = 1 modulo phi_f 
	*/
	if ( (*d * e)%phi_f ){
		printf("Ok.\n");
		return 1;
	}	
	else {
		printf("Error.\n");
		return -1;
	}
}
	
static void usage()
{
	printf("usage: enter values p q e\n");
	exit(1);
}

/*
* Public function used to externally interface with rsacracker
*/
int execute_rsa(long p, long q, long e, struct gcdstruct *gcds, 
				struct rowpointers *rps)
{
	// Calculate Euler's Totient
	long phi_f = (p-1)*(q-1);

	printf("\n------RSA-DECRYPT-LITE------\n");
	printf("Cracking d for N=%ld and e=%ld\n", p*q, e);
	printf("Euler's Totient = %ld\n", phi_f);

	gcd(phi_f, e, gcds, rps);
	
	crack_d(phi_f, gcds, rps);
	
	if (validate_d(phi_f, e, rps->b2))
		return 1;

	else return 0;
}

/* Example of how to interface with the decryption value cracker. */
int main(int argc, char * argv[])
{
	long p, q, e;
	struct gcdstruct gcds;
	struct rowpointers rps;

	if (argc != 4)
		usage();

	p = strtoul(argv[1], NULL, 0);
	q = strtoul(argv[2], NULL, 0);
	e = strtoul(argv[3], NULL, 0);
	
	if (e == -1){
		printf("e is too large for the implementation ... Exiting.\n");
		exit(1);
	}

	if (execute_rsa(p, q, e, &gcds, &rps))
		printf("The decryption value is: %ld\n\n", *(rps.b2));
	else 
		printf("Decryption Failed.\n\n");

	return 0;
}
