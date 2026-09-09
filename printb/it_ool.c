#include <stdio.h>
#include "printb.c"

int main() {
	/* & operator (Bits-As-BooleanArray): Goes down the line on each operand, comparing each bit on the byte. Every time two bits are both true, it adds true to the result. */
	/* | operator (Bits-As-BooleanArray): Same as the & operator, except it checks if either bit is true. */
	/* ^ operator (Bits-As-BooleanArray): Same as the & operator, except if either bit is true, it adds true to result, except if both are true, in which case it adds false to the result. The XOR operation.  */
	/* ~ operator (Bits-As-Boolean): Negates the operand and subtracts one from it. */
	/* && operator (Bits-As-Boolean): If both operands are at least 1, returns true (1). Otherwise, returns false (0). */
	/* || operator (Bits-As-Boolean): If either operand is at least 1, returns true (1). Otherwise, returns false (0). */
	/* != operator (Bits-As-Boolean): If both operands are the same, returns false (0). Otherwise, returns true (1). */
	/* ! operator (Bits-As-Boolean): If the operand is 0, return true (1). Otherwise, returns false (0). */
	/* << operator (Bits-As-BooleanArray): Shift all the bits in the first operand to the left by the distance in the second operator. */
	/* >> operator (Bits-As-BooleanArray): Shift all the bits in the first operand to the right by the distance in the second operator. */
	
	int i;
	for (i = 0; i < 11; i++) {
		int j;
		for (j = 0; j < 11; j++) {
			printf("(");
			printb(i);
			printf(", ");
			printb(j);
			printf("): ");
			printb(i << j);
			printf("\n");
			printf("(%d, %d): %d\n", i, j, i << j);
		}
	}

	return 0;
}
