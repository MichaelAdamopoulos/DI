/* File: main.c */

#include <stdio.h>
#include <stdlib.h>

#include "solve.h"							/* include the header file containing the prototype of function 'solve' */

int main(void) {

	int n , i , j ;
	int **graph ;

	scanf("%d", &n);						/* get number of nodes */
	if ( ( graph = malloc ( n * sizeof(int *) ) ) == NULL )		/* define a dynamic n x n array */
		return 1;						/* if memory allocation fails then return 1 */
	for ( i = 0 ; i < n ; i++ )
		if ( ( graph[i] = malloc ( n * sizeof(int) ) ) == NULL )
			return 1;
	for ( i = 1 ; i < n ; i++ )					/* fill the array with the cost of each edge */
		for ( j = 0 ; j < i ; j++ ) {
			scanf("%d", &graph[i][j]);
			graph[j][i] = graph[i][j];			/* Cij = Cji */
		}
	for ( i = 0 ; i < n ; i++ )
		graph[i][i] = 0 ;					/* Cii = 0 */
	solve ( n , graph );						/* call function 'solve' to initiate Floyd - Warshall algorithm */
	for ( i = 0 ; i < n ; i++ )
		free(graph[i]);						/* free all memory allocated by 'malloc' */
	free(graph);
	return 0;
}
