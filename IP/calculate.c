/* File: calculate.c */

#include <stdio.h>

int fun(int *p) {

	int ch , last_ch ;
	int result = 0 , result_2 = 0 ;
	int sign = 0 , last_sign = 0 , pros = 0 ;
	int error = 0 ;
	int cond = 0 , cond_2 = 1 , cond_3 = 0 , cond_4 = 0 , cond_5 = 0 ;
	int i = 0 ;

	while ( ( ( ch = getchar() ) != EOF ) && ( ch != '\n' ) ) {
		if ( ch == ')' ) {
			if ( last_sign )
				error = 1 ;
			result = ( sign == '+' ) ? result + result_2 : result - result_2 ;
			if ( !error )
				return result;
			else {
				return 0;
			}
		}
		else if ( ( ch >= '0' && ch <= '9' ) ) {
			cond_2 = 2 ;
			cond_5 = 0 ;
			last_ch = ch ;
			last_sign = 0 ;
			if ( cond ) {
				error = 1 ;
			}
			if ( sign == 0 ) {
				result = result * 10 + ch - '0' ;
			}
			else {
				result_2 = result_2 * 10 + ch - '0' ;
			}
		}
		else if ( ( ch == '+' || ch == '-' ) ) {
			if ( !cond_2 ) {
				error = 1 ;
			}
			if ( cond_3 ) {
				error = 0 ;
				cond_3 = 0 ;
			}
			if ( cond_5 )
				error = 1;
			if ( cond_4 ) {
				ch = ( pros == ch ) ? '+' : '-' ;
				cond_5 = 1 ;
			}
			cond_2--;
			cond_4 = 1 ;
			pros = ch ;
			result = ( sign == '+' ) ? result + result_2 : result - result_2 ;
			result_2 = 0 ;
			sign = ch ;
			cond = 0 ;
			last_ch = ch ;
			last_sign = 1 ;
		}
		else if ( ch == '\t' || ch == ' ' ) {
			if ( last_ch >= '0' && ch <= '9' ) {
				cond = 1 ;
			}
			else
				continue;
		}
		else if ( ch == '(' ) {
			if ( last_ch == '+' || last_ch == '-' )
				result_2 = fun(&error);
			else
				result_2 = - fun(&error);
			cond_3 = 1 ;
			if ( error == 10 ) {
				*p = 10 ;
				return 0;
			}
			if ( error == 100 ) {
				*p = 100 ;
				return 0;
			}
		}
		else
			error = 1;
		}
	*p = ( ch == EOF ) ? 10 : 100 ;
	return 0;
}

int main(void) {

	int ch , last_ch ;
	int result = 0 , result_2 = 0 ;
	int sign = 0 , last_sign = 0 , pros = 0 ;
	int error = 0 ;
	int cond = 0 , cond_2 = 1 , cond_3 = 0 , cond_4 = 0 , cond_5 = 0 ;
	int i = 0 ;
	int *p = &error ;

	while ( ( ch = getchar() ) != EOF ) {
		if ( ch == '\n' ) {
			i++;
			result = ( sign == '+' ) ? result + result_2 : result - result_2 ;
			if ( last_sign ) {
				error = 2 ;
			}
			if ( !error )
				printf("Result %d: %d\n", i, result);
			else
				if ( error == 1 )
					printf("Result %d: Unexpected character!\n", i);
				else if ( error == 2 )
					printf("Result %d: Unexpected end of input!\n", i);
				else
					printf("Result %d: Error!\n", i);
			result = 0 ;
			result_2 = 0 ;
			last_ch = 0 ;
			sign = 0 ;
			cond = 0 ;
			cond_2 = 1 ;
			cond_3 = 0 ;
			cond_4 = 0 ;
			cond_5 = 0 ;
			error = 0 ;
		}
		else if ( ( ch >= '0' && ch <= '9' ) ) {
			last_sign = 0 ;
			cond_2 = 2 ;
			cond_4 = 0 ;
			cond_5 = 0 ;
			last_ch = ch ;
			if ( cond ) {
				error = 1 ;
			}
			if ( sign == 0 ) {
				result = result * 10 + ch - '0' ;
			}
			else {
				result_2 = result_2 * 10 + ch - '0' ;
			}
		}
		else if ( ( ch == '+' || ch == '-' ) ) {
			if ( !cond_2 ) {
				error = 1 ;
			}
			if ( cond_3 ) {
				error = 0 ;
				cond_3 = 0 ;
			}
			if ( cond_5 )
				error = 1;
			if ( cond_4 ) {
				ch = ( pros == ch ) ? '+' : '-' ;
				cond_5 = 1 ;
			}
			cond_2--;
			cond_4 = 1 ;
			pros = ch ;
			result = ( sign == '+' ) ? result + result_2 : result - result_2 ;
			result_2 = 0 ;
			sign = ch ;
			cond = 0 ;
			last_ch = ch ;
			last_sign = 1 ;
		}
		else if ( ch == '\t' || ch == ' ' ) {
			if ( last_ch >= '0' && ch <= '9' )
				cond = 1 ;
			else
				continue;
		}
		else if ( ch == '(' ) {
			if ( last_ch == '+' || last_ch == '-' )
				result_2 = fun(&error);
			else
				result_2 = - fun(&error);
			cond_3 = 1 ;
			if ( error == 10 ) {
				printf("Result %d: Missing closing parenthesis!\n", i + 1);
				break;
			}
			if ( error == 100 ) {
				printf("Result %d: Missing closing parenthesis!\n", i + 1);
				result = 0 ;
				result_2 = 0 ;
				last_ch = 0 ;
				sign = 0 ;
				cond = 0 ;
				cond_2 = 1 ;
				cond_3 = 0 ;
				cond_4 = 0 ;
				cond_5 = 0 ;
				error = 0 ;
				continue;
			}
			last_sign = 0 ;
			cond_2 = 2 ;
			cond_4 = 0 ;
			cond_5 = 0 ;
		}
		else
			error = 1 ;
	}
	return 0;
}
