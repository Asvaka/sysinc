#include <stdio.h>
#include <stdint.h>

uint8_t num_to_b64(uint8_t num) {
	if (num < 26) {
		return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[num];
	}
	else if (num < 52) {
		return "abcdefghijklmnopqrstuvwxyz"[num - 26];
	}
	else if (num < 62) {
		return (num-52);
	}
	else if (num == 62) {
		return '+';
	}
	
	return '/';
}

unsigned end_24(unsigned i) {
        char t, *alias = (char *)&i;
        t = alias[2];
        alias[2] = alias[0];
        alias[0] = t;
        return i;
}

uint8_t conv32to8(uint32_t t, int i) {
	uint8_t tmp = t << (32-(6*i));
	tmp = tmp >> (32-6);
	tmp = tmp << (6*(i-1));
	return tmp;
}

int main() {
	char *str = "ABC";
	int i;
	uint32_t tmp = 0, tmp2 = 0;
	uint8_t *alias = (uint8_t *)&tmp, *alias2 = (uint8_t *)&tmp2;
	uint8_t test = 0;
	(void)tmp2;
	(void)alias;
	test = str[0];
	printf("%c\n", num_to_b64(((uint8_t)(test<<2))>>2));
	/*printf("%b\n", str[0]);
	printf("%b\n", ((uint8_t)(test<<2))>>2);*/
	printf("%lu\n", sizeof(test));

	for (i = 0; i < 3; i++) {
		tmp += ((uint32_t)str[i]) << (8*i);
	}
	tmp = end_24(tmp);
	/*printf("%024b\n", tmp);*/
	for (i = 3; i > -1; i--) {
		/*printf("%08b\n", num_to_b64(conv32to8(tmp, i)));*/
		printf("%c\n", num_to_b64(conv32to8(tmp, i)));
		tmp2 += num_to_b64(conv32to8(tmp, i));
		/*alias[i] = num_to_b64(alias[i]);*/
	}
	/*printf("%024b\n", tmp2);*/
	/*tmp = end_24(tmp);*/
	for (i = 0; i < 4; i++) {
		printf("%c", alias2[i]);
	}
	printf("\n");
	return 0;
}
