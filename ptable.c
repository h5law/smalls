/**
 * ptable.c
 * function abstraction using pointers
 **/
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "ptable-0.1dev"

void usage(char *prog) {
    fprintf(stderr,
        "Usage:\n"
        "$ %s [-hV] [-w WIDTH] [-f FUNC]\n"
        "          -h           Show this help screen\n"
        "          -V           Show the current version\n"
        "          -w WIDTH     Print WIDTHxWIDTH table, default=10\n"
        "          -f FUNC      Function to use for table, default='times'\n",
        prog);
}

int times(int a, int b) { return a * b; }
int square(int a, int b) { return (a * a) + (2 * a * b) + (b * b); }

const struct {
    const char *name;
    int (*f)(int, int);
} function_map [] = {
    {"times", times},
    {"square", square},
};

void printTable(int n, int (*f)(int, int)) {
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++) {
            printf("%4d", f(i, k));
        }
        putchar('\n');
    }
}

int call_function(const char *name, int width) {
    int len_name;
    len_name = sizeof(name);
    for (long unsigned int i = 0; i < (sizeof(function_map) / sizeof(function_map[0])); i++) {
        if (!strncmp(function_map[i].name, name, len_name) && function_map[i].f) {
            printTable(width, function_map[i].f);
            return 0;
        }
    }
    return -1;
}

int main(int argc, char **argv) {
    int opt;
    int width = 10;
    char *operation = "times";
    for (int ind = optind; ind < argc; ind++) {
        if ((opt = getopt(argc, argv, "hVw:f:")) != -1) {
            switch (opt) {
                case 'h':
                    usage(argv[0]);
                    exit(0);
                    break;
                case 'V':
                    printf("%s\n", VERSION);
                    exit(0);
                    break;
                case 'w':
                    width = strtol(optarg, NULL, 0);
                    break;
                case 'f':
                    operation = optarg;
                    break;
                default:
                    usage(argv[0]);
                    exit(1);
                    break;
            }
        }
    }

    call_function(operation, width);
    return 0;
}
