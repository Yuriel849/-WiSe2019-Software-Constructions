/* Author	   : Myungjun Kim
   Contents    : Print a chessboard in a two-dimensional order to the console.
   Instructions: 1. Use for loops to print all fields of a chessboard in a two-dimensional order to the console.
				 2. Rows are labeled 8 (top) to 1 (bottom).
				 3. Columns are labeled a (left) to h (right).
   Note		   : Modified version of file lab2a.c to receive input from the user with scanf().
 */

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int main()
{	
	// Variables to represent the row numbers and column characters.
	int rowNumber = 8;
	char columnChar = 'a';

	// Use two for loops, one inside the other. The outer loop prints each row.
	for (int i = (2 * rowNumber + 1); i > 0; i--) {
		if (i % 2 == 1) { // If this is an odd-numbered row, print pluses and dashes.
			printf("\n+----+----+----+----+----+----+----+----+\n");
		}
		else { // If this is an even-numbered row, print bars and identifiers with the inner for loop.
			printf("| "); // First leftmost bar.
			// The inner loop prints the contents of each row.
			for (int j = columnChar; j <= 'h'; j++) { // columnChar remains unchanged
				printf("%c%d | ", j, i / 2);
			}
		}
	}
}