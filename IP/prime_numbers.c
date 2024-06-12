/* File: prime_numbers.c */
#include <stdio.h>
#include <math.h>
#define START 1990000001
#define FINISH 1999999999

int main()

{ long i, d, sum;
  sum = 0;
  for ( i = START; i <= FINISH; i = i + 2 ) {
  	sum++;
  	for ( d = 2; d <= ( (long) sqrt(i) ); d++ ) {
  		if ( ( i % d ) == 0 ) {
  			d = ( (long) sqrt(i) );
  			sum--;
  		}
  	}
  }
  printf ("There are %7ld prime numbers between 1.990.000.000 and 2.000.000.000!", sum);
}
