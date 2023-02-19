#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/log/log.h"

#define MAX_ALLOCS 1000000

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
int main(int argc, char* argv[])
{
    char* ptr[MAX_ALLOCS];
    char* eptr;

    // check usage
    if (argc < 3) {
        fprintf(stderr, "usage: %s num_allocs block-size [step [min [max]]]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_allocs = strtol(argv[1], &eptr, 10);
    if (*eptr != '\0')
        log_fatalf("strtol(): %s\n", argv[1]);
    if (num_allocs > MAX_ALLOCS)
        log_fatalf("num_allocs > %d\n", MAX_ALLOCS);

    int blocksize = strtol(argv[2], &eptr, 10);
    if (*eptr != '\0')
        log_fatalf("strtol(): %s\n", argv[2]);

    int free_step = 1;
    if (argc > 3) {
        free_step = strtol(argv[3], &eptr, 10);
        if (*eptr != '\0')
            log_fatalf("strtol(): %s\n", argv[3]);
    }

    int free_min = 1;
    if (argc > 4) {
        free_min = strtol(argv[4], &eptr, 10);
        if (*eptr != '\0')
            log_fatalf("strtol(): %s\n", argv[4]);
    }

    int free_max = num_allocs;
    if (argc > 5) {
        free_max = strtol(argv[5], &eptr, 10);
        if (*eptr != '\0')
            log_fatalf("strtol(): %s\n", argv[5]);
    }

    if (free_max > num_allocs)
        log_fatalf("free-max > num-allocs\n");

    printf("initial program break: %10p\n", sbrk(0));
    printf("allocating %d*%d bytes\n", num_allocs, blocksize);
    for (int j = 0; j < num_allocs; j++) {
        ptr[j] = malloc(blocksize);
        if (ptr[j] == NULL)
            log_fatalf("malloc: %s", strerror(errno));
    }
    printf("program break is now: %10p\n", sbrk(0));

    printf("freeing blocks from %d to %d in steps of %d\n", free_min, free_max, free_step);
    for (int j = free_min - 1; j < free_max; j += free_step) {
        free(ptr[j]);
    }
    printf("after free(), program break is: %10p\n", sbrk(0));

    exit(EXIT_SUCCESS);
}
#pragma GCC diagnostic pop
