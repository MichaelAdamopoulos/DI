/* FIle: milrab.c */

#include <stdio.h>
#include <time.h>
#define MINNUM 3990000000
#define MAXNUM 4010000000

int main ()

{
	clock_t time_1, time_2 ;

	time_1 = clock() ;						  /* start deterministic algorithm timer */

	char cond ;
	int dev ;									       /* devider tested */
	int sum = 0 ;									        /* sum of primes */
	unsigned int num ;								        /* number tested */

	for ( num = MINNUM | 1 ; num < MAXNUM ; num += 2 ) {	     /* check all odd numbers in [MINNUM,MAXNUM] */
		if ( num % 3 ) {
			cond = 1 ;
			for ( dev = 5 ; dev * dev <= num ; dev += 6 ) {
								       /* check all odd numbers not devided by 3 */
				if ( ( ( num % dev ) == 0 ) || ( num % ( dev + 2 ) == 0 ) ) {
					cond = 0 ;
					break;	  /* if num has a devider stop checking and make condition false */
				}
			}
			if ( cond ) {				       /* if condition is true then num is prime */
				sum++;
			}
		}
	}

	time_1 = clock() - time_1 ;					    /* end deterministic algorithm timer */

	char i, j, r ;
	int tot = 0 ;									        /* sum of primes */
	unsigned int n, current, d, x ;							    /* n : number tested */
	unsigned long long a ;

	time_2 = clock() ;						   /* start miller-rabin algorithm timer */

	for ( n = MINNUM | 1 ; n < MAXNUM ; n += 2 ) {		     /* check all odd numbers in [MINNUM,MAXNUM] */
		current = n - 1 ;			     /* write n - 1  as ( 2 ^ r ) * d , where "d" is odd */
		r = 0 ;
		while ( current % 2 == 0 ) {
			current = current / 2 ;
			r++;
		}
		for ( i = 1 ; i < 4 ; i++ ) {			        /* 3 loops for 3 different values of "a" */
			d = current ;
			if ( i == 1 ) {
				a = 2 ;
			}
			else if ( i == 2 ) {
				a = 7 ;
			}
			else a = 61 ;
			x = 1 ;								  /* calculate a^d mod n */
			a = a % n ;
			while ( d > 0 ) {
				if ( d % 2 == 1 ) {
					x = ( x * a ) % n ;
				}
				d >>= 1 ;
				a = ( a * a ) % n ;
			}
			if ( x == 1 || x == n - 1 )	{
				continue;			        /* if condition is true move to next "a" */
			}
			for ( j = 1 ; j < r ; j++ ) {
				x = ( ( (unsigned long long) x % n ) * ( (unsigned long long) x % n ) ) % n ;
							     /* calculate x^2 mod n, casting to prevent overflow */
				if ( x == n - 1 ) {
					break;	      /* if condition is true stop the loop and move to next "a" */
				}
			}
			if ( j == r ) {
				break;	     /* if loop is completed then condition is false so "n" is not prime */
			}
		}
		if ( i == 4 ) {		   /* if all 3 conditions are true ( 1 for each loop ) then "n" is prime */
			tot++;
		}
	}

	time_2 = clock() - time_2 ;					     /* end miller-rabin algorithm timer */

	printf ("Checking range [3990000000,4010000000] for primes\n");

	printf ("Deterministic algorithm: Found %d primes in %2.2f secs\n", sum, (double) time_1 / CLOCKS_PER_SEC);

	printf ("Miller-Rabin algorithm: Found %d primes in %2.2f secs\n", tot, (double) time_2 / CLOCKS_PER_SEC);
}
