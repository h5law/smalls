#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#define PROG "group"
#define VERSION "group-0.1_dev"

const char *errstr[] = {
        "",
/* 1*/  "usage: %s [-hV] [-n INT] [-f CHAR] STRING\n",
/* 2*/  "version: %s\n",
};

void grouper(char *string, int width, char filler) {
    char *str;
    int remainder, padded, i;

    if ((strlen(string) % width) != 0) {
        remainder = strlen(string) % width;
        padded = strlen(string) + (width - remainder);
    } else {
        padded = strlen(string);
    }

    str = (char *) malloc(padded);
    memset(str, filler, padded);
    strncpy(str, string, strlen(string));

    for (i = 0; i < padded; i++) {
        putchar(str[i]);
        if (((i + 1) % width) == 0)
            putchar('\n');
    }
}

int main(int argc, char *argv[]) {

    char *iterable;
    char filler = ' ';
    int group = 3;

    int opt, ind;
    for (ind = optind; ind < argc; ind++) {
        if ((opt = getopt(argc, argv, "hVn:f:")) != -1) {
            switch (opt) {
                case 'h':
                    fprintf(stderr, errstr[1], PROG);
                    return 1;
                case 'V':
                    printf(errstr[2], VERSION);
                    return 0;
                case 'n':
                    if ((group = atoi(optarg)) == 0) {
                        fprintf(stderr, errstr[1], PROG);
                        return 1;
                    }
                    break;
                case 'f':
                    strncpy(&filler, optarg, 1);
                    break;
                default:
                    abort();
            }
        }
    }

    memset(iterable, '\0', 1);
    for (ind = optind; ind < argc; ind++)
        strcat(iterable, argv[ind]);

    if (iterable[0] == '\0') {
        fprintf(stderr, errstr[1], PROG);
        return 1;
    }

    grouper(iterable, group, filler);

    return 0;
}
