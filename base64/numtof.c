#include <stdio.h>

int main() {
        FILE *fp;
        char i, j, k;
        printf("Character to write:\n");
        scanf("%hhd", &i);
        printf("Number of times to write:\n");
        scanf("%hhd", &j);
        fp = fopen("out.txt","w");
        for (k = 0; k < j; k++) {
                fwrite(&i, 1, 1, fp);
        }
        return 0;
}
