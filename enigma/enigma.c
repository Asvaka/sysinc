#include <stdio.h>
#include <stdlib.h>

#define FASTR "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define MEDIUMR "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define SLOWR "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define REFLECTR "IXUHFEZDAOMTKQJWNSRLCYPBVG"

#define FASTRI "TAGBPCSDQEUFVNZHYIXJWLRKOM"
#define MEDIUMRI "AJPCZWRLFBDKOTYUQGENHXMIVS"
#define SLOWRI "UWYGADFPVZBECKMTHXSLRINQOJ"

#define NUM_CHAR 26

char s(char c, int l) {
	if (l < 0) {
		return (((((c - 'A') + l) % NUM_CHAR) + 26) % NUM_CHAR) + 'A';
	}
	return (((c - 'A') + l) % NUM_CHAR) + 'A';
}	

// r == 0 is fast rotor, r == 1 is medium rotor, r == 2 is slow rotor
char shift_char(char c, int l, int r) {
	if (l == 1) {
		printf("Current character & character number: %c %d\n", c, l);
	}
	if (r == 0) {
		return s(c, l);
	} else if (r == 1) {
		return s(c, l / NUM_CHAR);
	} else if (r == 2) {
		return s(c, (l / NUM_CHAR) / NUM_CHAR);
	}
	return c;
}

char rapply(char c, char *r) {
	return r[c - 'A'];
}

char shiply(char c, int l, char *r, int rn) {
	if (rn == 3) {
		return rapply(c, r);
	}
	return shift_char(rapply(shift_char(c, l, rn), r), -l, rn);
}

char encrypt_char (char c, int l) {
	return shiply(
			shiply(
				shiply(
					shiply(
						shiply(
							shiply(
								shiply(c, l, FASTR, 0)
							, l, MEDIUMR, 1)
						, l, SLOWR, 2)
					, l, REFLECTR, 3)
				, l, SLOWRI, 2)
			, l, MEDIUMRI, 1)
		, l, FASTRI, 0);
}

int main(int argc, char **argv) {
	int input_len = 0;
	while (argv[1][input_len] != '\0') {
		printf("%c\n", argv[1][input_len]);
		input_len++;
	}
	
	char post[input_len];
	for (int i = 0; i < input_len; i++) {
		post[i] = encrypt_char(argv[1][i], i + 1);
	}
	
	printf("Encrypted Text: ");
	for (int i = 0; i < input_len; i++) {
		printf("%c", post[i]);
	}
	printf("\n");	
	
	return 0;
}
