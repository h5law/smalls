/**
 * pascal.c
 * generate a tree of n height of pascal's triangle
 **/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define PROG "pascal"
#define VERSION "0.0.1-dev"

void print_coef(int rows, int start) {
    int coef = 1;
    int i, j;
    for (i = start; i < rows; i++) {
        printf("%4d: ", i);
        for (j = 0; j <= i; j++) {
            if (j == 0 || i == 0)
                coef = 1;
            else
                coef = coef * (i - j + 1) / j;
             printf(" %d", coef);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    int opt;
    unsigned int rows = 5;
    unsigned int start = 0;
    for (int ind = optind; ind < argc; ind++) {
        if ((opt = getopt(argc, argv, "hVr:s:")) != -1) {
            switch (opt) {
                case 'h':
                    fprintf(stderr,
                            "Usage: $ %s [-hV] [-r ROWS] [-s START]\n",
                            PROG);
                    exit(0);
                    break;
                case 'V':
                    printf("%s_%s\n", PROG, VERSION);
                    exit(0);
                    break;
                case 'r':
                    rows = strtol(optarg, NULL, 0);
                    break;
                case 's':
                    start = strtol(optarg, NULL, 0);
                    break;
            }
        }
    }
    print_coef(rows, start);
    return 0;
}
