#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

#include "../lib/getnum/getnum.h"
#include "../lib/log/log.h"

static void display_process_times(const char *msg)
{
    static long clock_ticks = 0;

    if (msg != NULL)
        printf("%s", msg);

    // Fetch clock ticks on first call
    if (clock_ticks == 0) {
        clock_ticks = sysconf(_SC_CLK_TCK);
        if (clock_ticks == -1)
            log_fatal("sysconf");
    }

    clock_t clock_time = clock();
    if (clock_time == -1)
        log_fatal("clock");

    printf("clock() returns: %ld clocks-per-sec (%.2f secs)\n",
        (long)clock_time,
        (double)clock_time / CLOCKS_PER_SEC);

    struct tms t;
    if (times(&t) == -1)
        log_fatal("times");

    printf("times() yields: user CPU=%.2f; system CPU: %.2f\n",
        (double)t.tms_utime / clock_ticks,
        (double)t.tms_stime / clock_ticks);
}

int main(int argc, char *argv[])
{
    printf("CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n\n",
        (long)CLOCKS_PER_SEC,
        sysconf(_SC_CLK_TCK));

    display_process_times("At program start:\n");

    int num_calls = 100000000;
    if (argc > 1)
        num_calls = get_int(argv[1]);

    for (int i = 0; i < num_calls; i++)
        (void)getppid();

    printf("\n");
    display_process_times("After getppid() loop:\n");

    exit(EXIT_SUCCESS);
}
