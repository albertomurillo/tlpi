#define _XOPEN_SOURCE

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lib/log/log.h"

#define SBUF_SIZE 1000

int main(int argc, char *argv[])
{

    if (argc < 3) {
        fprintf(stderr, "usage: %s input-date-time in-format [out-format]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Use locale settings in conversions
    if (setlocale(LC_ALL, "") == NULL)
        log_fatal("setlocale()");

    // Initialize 'tm'
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    if (strptime(argv[1], argv[2], &tm) == NULL)
        log_fatal("strptime()");
    // Not set by strptime(); tells mktime() to determine if DST is in effect
    tm.tm_isdst = -1;

    printf("calendar time (seconds since Epoch): %ld\n", (long)mktime(&tm));

    char sbuf[SBUF_SIZE];
    char *output_format = (argc > 3) ? argv[3] : "%H:%M:%S %A, %d %B %Y %Z";
    if (strftime(sbuf, SBUF_SIZE, output_format, &tm) == 0)
        log_fatal("strftime() returned 0");

    printf("strfmtime() yields: %s\n", sbuf);
    exit(EXIT_SUCCESS);
}
