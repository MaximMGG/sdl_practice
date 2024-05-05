//green.bmp
#include <stdio.h>


int main() {

    FILE *f = fopen("green.bmp", "r");

    while(!feof(f)) {
        char c;

        fread(&c, 1, 1, f);
        if (c == '-') {

        } else if (c == 1) {

        } else if (c == 100) {
            printf("\n");
        }
        else {
            printf("%d", c);
        }


    }

    fclose(f);
    return 0;
}
