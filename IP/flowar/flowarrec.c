/* File: flowarrec.c */

#include <stdio.h>

int shortlen ( int i , int j , int k , int **graph );								/* prototype of function 'shortlen' */

void solve ( int n , int **graph ) {

	int i , j , leng ;

	for ( i = 1 ; i < n ; i++ ) {										/* print lenght of shortest path between all edges */
		printf("\n");
		for ( j = 0 ; j < i ; j++ ) {
			leng = shortlen ( i , j , n - 1 , graph );							/* call function 'shortlen' to calculate lenght of shortest path */
			if ( leng == -1 )
				printf("From node %d to node %d: There is no path\n", i , j );
			else
				printf("From node %d to node %d: Length of shortest path is %d\n", i , j , leng );
		}
	}
	return;
}
int shortlen ( int i , int j , int k , int **graph ) {			/* recursive Floyd - Warshall algorithm */

	int a , b , c ;

	if ( k == -1 ) {						/* if k = -1 return Cij, unless Cij = -1 meaning there is no path */
		if ( graph[i][j] == -1 )
			return -1;
		else
			return graph[i][j];
	}
	else {								/* else initiate recursion */
		a = shortlen ( i , j , k - 1 , graph );			/* calculate Pi,j,k-1 */
		b = shortlen ( i , k , k - 1 , graph );			/* calculate Pi,k,k-1 */
		c = shortlen ( k , j , k - 1 , graph );			/* calculate Pk,j,k-1 */
		if ( a != -1 && b != -1 && c != -1 )			/* if both path 'a' and 'b+c' exist */
			return ( a > b + c ? b + c : a );		/* return min { Pi,j,k-1 , Pi,k,k-1 + Pk,j,k-1 } */
		else if ( a == -1 )					/* else return lenght of proper path if it exists */
			return ( ( b == -1 || c == -1 ) ? -1 : b + c );
		else if ( b == -1 || c == -1 )
			return a;
	}
}
