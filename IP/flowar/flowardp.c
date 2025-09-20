/* File: flowardp.c */

#include <stdio.h>
#include <stdlib.h>

void solve( int n , int **graph ) {

	int i , j , k ;
	int **Q;
	int next[n][n];

	if ( ( Q = malloc ( n * sizeof(int *) ) ) == NULL )							/* define a dynamic n x n array */
		return;												/* if memory allocation fails end function */
	for ( i = 0 ; i < n ; i++ )
		if ( ( Q[i] = malloc ( n * sizeof(int) ) ) == NULL )
			return;
	for ( i = 0 ; i < n ; i++ )
		for ( j = 0 ; j < n ; j++ ) {
			Q[i][j] = graph[i][j];									/* fill 'Q' array with cost between all edges */
			next[i][j] = j;										/* fill array 'next' */
		}
	for ( k = 0 ; k < n ; k++ )										/* dynamic Floyd - Warshall algorithm */
		for ( i = 0 ; i < n ; i++ )
			for ( j = 0 ; j < n ; j++ )
				if ( Q[i][j] == -1 )
					if ( Q[i][k] == -1 || Q[k][j] == -1 )
						Q[i][j] = -1;
					else {
						Q[i][j] = Q[i][k] + Q[k][j];
						next[i][j] = next[i][k];
					}
				else if ( Q[i][k] == -1 || Q[k][j] == -1 )
					Q[i][j] = Q[i][j];
				else if ( Q[i][j] > Q[i][k] + Q[k][j] ) {
					Q[i][j] = Q[i][k] + Q[k][j];
					next[i][j] = next[i][k];
				}
	for ( i = 1 ; i < n ; i++ ) {										/* print lenght of shortest path between all edges */
		printf("\n");
		for ( j = 0 ; j < i ; j++ ) {
			if ( Q[i][j] == -1 ) {
				printf("From node %d to node %d: There is no path\n", i , j );
				continue;									/* if there is no path continue with calculation of next path */
			}
			printf("From node %d to node %d: Length of shortest path is %d\n", i , j , Q[i][j]);
			#ifdef PATH										/* if PATH is defined, also print shortest path */
			k = i;
			printf("\tShortest path is: %d", k);
			while ( k != j ) {									/* path reconstruction algorithm */
				k = next[k][j];
				printf(" -> %d", k);
			}
			printf("\n");
			#endif
		}
	}
	for ( i = 0 ; i < n ; i++ )										/* free all memory allocated by 'malloc' */
		free(Q[i]);
	free(Q);
	return;
}

