#include <stdio.h>
#include "printb.c"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define CHOICE(e, f, g) (((e)&(f))|((~(e))&(g)))
#define MEDIAN(e, f, g) ((((e)|(f))&(g))|(((f)|(g))&(e)))
#define LOTATE(e, f) (((e)<<(f))|((e)>>((sizeof(e)*8)-f)))
#define ROTATE(e, f) (((e)>>(f))|((e)<<((sizeof(e)*8)-f)))

int main() {
	/* 00001111 /
	int a = 15;
	/ 00110011 /
	int b = 51;
	/ 01010101 /
	int c = 85;*/
	/* 00101101 = 45*/
	unsigned int d = 0xABCD0123;
	
	/*printf("%08lX, 04: %08lX\n", d, ROTATE(d, 4));*/
	/*int i;
	for (i = 0; i < 4; i++) {
		printb(ROTATE(d, 4));
	}*/
	
	printf("Pretate: ");
	printb(d);
	printf("\nRotated: ");
	printb(ROTATE(d, 4));
	printf("\n");
	printf("%lu", (sizeof(d)*8)-4);
	printf("\n");

	/*int i;
	for (i = 0; i < 9; i++) {
		printb(ROTATE(d,i));
		printf("\n");
	}*/
	/*printf("%d\n", CHOICE(a, b, c));*/
	
	return 0;
}
