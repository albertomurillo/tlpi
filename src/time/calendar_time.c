#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "../lib/log/log.h"

#define SECONDS_IN_TROPICAL_YEAR (365.24219 * 24 * 60 * 60)

static void tm_print(const struct tm *tm)
{
    printf("struct tm {\n");
    printf("  int tm_sec   = %d\n", tm->tm_sec);
    printf("  int tm_min   = %d\n", tm->tm_min);
    printf("  int tm_hour  = %d\n", tm->tm_hour);
    printf("  int tm_mday  = %d\n", tm->tm_mday);
    printf("  int tm_mon   = %d\n", tm->tm_mon);
    printf("  int tm_year  = %d\n", tm->tm_year);
    printf("  int tm_wday  = %d\n", tm->tm_wday);
    printf("  int tm_yday  = %d\n", tm->tm_yday);
    printf("  int tm_isdst = %d\n", tm->tm_isdst);
    printf("}\n");
};

int main(int argc, char *argv[])
{
    time_t t = time(NULL);
    printf("time() returned seconds since the Epoch (1 Jan 1070): %ld", t);
    printf(" about %6.3f years\n", (double)t / SECONDS_IN_TROPICAL_YEAR);
    printf("\n");

    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
        log_fatalf("gettimeofday(): %s\n", strerror(errno));
    printf("gettimeofday() returned:\n");
    printf("struct timeval {\n");
    printf("    time_t      tv_sec  = %ld\n", tv.tv_sec);
    printf("    suseconds_t tv_usec = %ld\n", (long)tv.tv_usec);
    printf("}\n");
    printf("\n");

    const struct tm *gmp = gmtime(&t);
    if (gmp == NULL)
        log_fatalf("gmtime(): %s\n", strerror(errno));
    // gmtime() returns a pointer to a statically allocated "struct tm",
    // we should save a copy since future calls will overwrite it
    struct tm gm = *gmp;
    printf("time() broken down by gmtime() returned:\n");
    tm_print(&gm);
    printf("\n");

    const struct tm *locp = localtime(&t);
    if (locp == NULL)
        log_fatalf("localtime(): %s\n", strerror(errno));
    // localtime() returns a pointer to a statically allocated "struct tm",
    // we should save a copy since future calls will overwrite it
    struct tm loc = *locp;
    printf("time() broken down by localtime() returned:\n");
    tm_print(&loc);
    printf("\n");

    printf("asctime() formats the gmtime() value as: %s", asctime(&gm));
    printf("ctime()   formats the time()   value as: %s", ctime(&t));
    printf("\n");

    printf("mktime() of gmtime()    value: %ld secs\n", mktime(&gm));
    printf("mktime() of localtime() value: %ld secs\n", mktime(&loc));

    exit(EXIT_SUCCESS);
}
