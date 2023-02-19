#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../log/log.h"
#include "getnum.h"

int get_int(const char* str)
{
    long num = get_long(str);
    if (num < INT_MIN || num > INT_MAX)
        log_fatalf("strtol(\"%s\"): integer out of range\n", str);
    return num;
}

long get_long(const char* str)
{
    char* eptr;

    if (str == NULL || *str == '\0')
        log_fatal("strtol(\"\"): null or empty string\n");

    errno = 0;
    long num = strtol(str, &eptr, 0);
    if (errno != 0)
        log_fatalf("strtol(\"%s\"): %s\n", str, strerror(errno));

    if (*eptr != '\0')
        log_fatalf("strtol(\"%s\"): nonnumeric characters\n", str);

    return num;
}
