#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/log/log.h"

#define BUF_SIZE 1000

// Return a steing containing the current rime formatted according to
// the specification in 'format' (see strftime(3) for specifiers).
// If 'format' is NULL, we use "%c" as a specifier (which gives the
// date and time as for ctime(3), but without the trailing newline).
// Returns NULL on error.
char *current_time(const char *format)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if (tm == NULL)
        return NULL;

    static char buf[BUF_SIZE]; // Nonreentrant
    size_t s = strftime(buf, BUF_SIZE, (format != NULL) ? format : "%c", tm);
    if (s == 0)
        return NULL;

    return buf;
}

int main(int argc, char *argv[])
{
    char *format = NULL;
    if (argc > 1)
        format = argv[1];

    char *msg;
    msg = current_time(format);
    if (msg == NULL)
        log_fatal("current_time");

    printf("Current time is: %s\n", msg);
    exit(EXIT_SUCCESS);
}
