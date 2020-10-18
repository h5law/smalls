/*
 * string.c
 * A tool to convert string into: binary, hexadecimal, decimal, etc.
 */
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PROG "permutation"
#define VERSION "0.1_dev"

char *errstr[] = {
        "",
/* 1 */ "usage: %s [-hV] [-r INT] ITERABLE\n",
/* 2 */ "version: %s-%s\n",
};

void combination(char *s, char *d, int start, int end, int ind, int r) {
    if (ind == r) {
        for (int j = 0; j < r; j++)
            printf("%c ", d[j]);
        putchar('\n');
        return;
    }

    for (int i = start; i <= end && (end - i + 1) >= (r - ind); i++) {
        d[ind] = s[i];
        combination(s, d, i + 1, end, ind + 1, r);
    }
}

void permute(char *s, int r, int i, int n) {
    char data[r];
    combination(s, data, 0, n - 1, 0, r);
}

int main(int argc, char **argv) {
    int ropt = 1;
    char *str;

    while (1) {
        int c = getopt(argc, argv, "hVr:");
        if (c == -1)
            break;
        switch (c) {
            case 'h':
                fprintf(stderr, errstr[1], PROG);
                return 1;
            case 'V':
                fprintf(stderr, errstr[2], PROG, VERSION);
                return 1;
            case 'r':
                ropt = strtol(optarg, NULL, 0);
                break;
            default:
                abort();
        }
    }

    str = (char *) malloc(512 * sizeof(char *));
    memset(str, '\0', 1);
    if (optind < argc) {
        while (optind < argc) {
            strcat(str, argv[optind]);
            optind++;
        }
        if (str[0] == '\0') {
            fprintf(stderr, errstr[1], PROG);
            return 1;
        }
    }

    permute(str, ropt, 0, strlen(str));

    return 0;
}
