/* File: exercise6.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "functions.h"

int main(void) {

	ArrayType Dictionary  = WordArray();			// create an array with the dictionary's words
	conversion("dog","cat",Dictionary);			// calling conversion to convert some words
	conversion("cans","coin",Dictionary);
	conversion("dart","dogs",Dictionary);
	conversion("zoologists","zaporozhye",Dictionary);
}
