#include <stdio.h>
#include <stdlib.h>

void print_help() {
    printf("Usage: range [M] N [S]\n");
    printf("Arguments (positional):\n");
    printf("  N      - end.               prints: 0, 1, ..., N-1\n");
    printf("  M N    - start and end.     prints: M, M+1, ..., N-1\n");
    printf("  M N S  - start, end, step.  prints: M, M+S, ..., until N\n");
    printf("\n");
    printf("Examples:\n");
    printf("  range 5        -> 0 1 2 3 4\n");
    printf("  range 2 7      -> 2 3 4 5 6\n");
    printf("  range 0 10 2   -> 0 2 4 6 8\n");
    printf("  range 10 0 -2  -> 10 8 6 4 2\n");
}

void print_range(int start, int end, int step) {
    int i = start;

    if (step > 0)
        for (i = start; i < end; i += step)
            printf("%d\n", i);
    else
        for (i = start; i > end; i += step)
            printf("%d\n", i);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }

    int start, end, step;
    switch (argc) {
        case 2:
            start = 0;
            end = atoi(argv[1]);
            step = 1;
            break;
        case 3:
            start = atoi(argv[1]);
            end = atoi(argv[2]);
            step = 1;
            break;
        case 4:
            start = atoi(argv[1]);
            end = atoi(argv[2]);
            step = atoi(argv[3]);
            break;
        default:
            fprintf(stderr, "got too many arguments\n");
            return 1;
    }

    print_range(start, end, step);
    return 0;
}
