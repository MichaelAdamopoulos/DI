/* File: flowarmem.c */

#include <stdio.h>
#include <stdlib.h>

int shortlen ( int i , int j , int k , int **graph , int ***px );							/* include prototype of function 'shortlen' */

void solve( int n , int **graph ) {

	int i , j , z , leng ;
	int ***px;

	if ( ( px = malloc ( n * sizeof(int **) ) ) == NULL )								/* define a dynamic n x n x n array */
		return;													/* if memory allocation fails end function */
	for ( i = 0 ; i < n ; i++ )
		if ( ( px[i] = malloc ( n * sizeof(int *) ) ) == NULL )
			return;
	for ( i = 0 ; i < n ; i++ )
		for ( j = 0 ; j < n ; j++ )
		if ( ( px[i][j] = malloc ( n * sizeof(int) ) ) == NULL )
			return;
	for ( i = 0 ; i < n ; i++ )
		for ( j = 0 ; j < n ; j++ )
			for ( z = 0 ; z < n ; z++ )
				px[i][j][z] = -108;									/* initialize px[i][j][z] to -108 for all i , j , z */
	for ( i = 1 ; i < n ; i++ ) {											/* print shortest lenght between all edges */
		printf("\n");
		for ( j = 0 ; j < i ; j++ ) {
			leng = shortlen ( i , j , n - 1 , graph , px );							/* call function 'shortlen' to calculate path with shortest lenght */
			if ( leng == -1 )
				printf("From node %d to node %d: There is no path\n", i , j );
			else
				printf("From node %d to node %d: Length of shortest path is %d\n", i , j , leng );
		}
	}
	for ( i = 0 ; i < n ; i++ )											/* free all memory allocated by 'malloc' */
		for ( j = 0 ; j < n ; j++ )
			free(px[i][j]);
	for ( i = 0 ; i < n ; i++ )
		free(px[i]);
	free(px);
	return;
}

int shortlen ( int i , int j , int k , int **graph , int ***px ) {		/* recursive with memoization Floyd - Warshall algorithm */

	int a , b , c ;

	if ( k == -1 ) {							/* if = -1 return Cij unless Cij = -1 meaning there is no path */
		if ( graph[i][j] == -1 )
			return -1;
		else
			return graph[i][j];
	}
	else {									/* else initiate recursion */
		if ( px[i][j][k] != -108 )					/* if px[i][j][k] was previously calculated skip recursive re-calculation */
			a = px[i][j][k];
		else {								/* else calculate px[i][j][k] */
			px[i][j][k] = shortlen ( i , j , k - 1 , graph , px );	/* calculate Pi,j,k-1 */
			a = px[i][j][k];
		}
		if ( px[i][k][k] != -108 )
			b = px[i][k][k];
		else {
			px[i][k][k] = shortlen ( i , k , k - 1 , graph , px ); /* calculate Pi,k,k-1 */
			b = px[i][k][k];
		}
		if ( px[k][j][k] != -108 )
			c = px[k][j][k];
		else {
			px[k][j][k] = shortlen ( k , j , k - 1 , graph , px );	/* calculate Pk,j,k-1 */
			c = px[k][j][k];
		}
		if ( a != -1 && b != -1 && c != -1 )				/* if both path 'a' and 'b+c' exist */
			return ( a > b + c ? b + c : a );			/* return min { Pi,j,k-1 , Pi,k,k-1 + Pk,j,k-1 } */
		else if ( a == -1 )						/* else return lenght of proper path if it exists */
			return ( ( b == -1 || c == -1 ) ? -1 : b + c );
		else if ( b == -1 || c == -1 )
			return a;
	}
}
