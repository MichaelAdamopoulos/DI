/* File: humble_numbers */

#include <stdio.h>
#define FINISH 5842

int main()

{ int i;
  int counter;
  int current;
  int a;
  a = 1;
  counter = 1;

  for ( i = 2; counter != FINISH; i++ ) {
	current = i;
	while ( ( current % 2 ) == 0 ) {
		current = ( current / 2 );
	}
	while ( ( current % 3 ) == 0 ) {
		current = ( current / 3 );
	}
	while ( ( current % 5 ) == 0 ) {
		current = ( current / 5 );
	}
	while ( ( current % 7 ) == 0 ) {
		current = ( current / 7 );
	}
	if ( current == 1 ) {
		counter++;
	}
 	if ( counter == FINISH ) {
		i--;
	}
  }
  printf ("The 5842th humble number is %d !", i);
}

