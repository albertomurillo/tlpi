#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/getnum/getnum.h"
#include "../lib/log/log.h"

#define MAX_ALLOCS 1000000

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
int main(int argc, char* argv[])
{
    char* ptr[MAX_ALLOCS];

    if (argc < 3) {
        fprintf(stderr, "usage: %s num_allocs block-size [step [min [max]]]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_allocs = get_int(argv[1]);
    if (num_allocs > MAX_ALLOCS)
        log_fatalf("num_allocs > %d\n", MAX_ALLOCS);
    int blocksize = get_int(argv[2]);
    int free_step = (argc > 3) ? get_int(argv[3]) : 1;
    int free_min = (argc > 4) ? get_int(argv[4]) : 1;
    int free_max = (argc > 5) ? get_int(argv[5]) : num_allocs;
    if (free_max > num_allocs)
        log_fatalf("free-max > num-allocs\n");

    printf("initial program break: %10p\n", sbrk(0));
    printf("allocating %d*%d bytes\n", num_allocs, blocksize);
    for (int j = 0; j < num_allocs; j++) {
        ptr[j] = malloc(blocksize);
        if (ptr[j] == NULL)
            log_fatalf("malloc(): %s", strerror(errno));
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
