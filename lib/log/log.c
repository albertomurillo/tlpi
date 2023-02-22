#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"

void log_fatal(const char* msg)
{
    fprintf(stderr, "[FATAL] %s\n", msg);
    exit(EXIT_FAILURE);
}

void log_fatalf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[FATAL] ");
    vfprintf(stderr, format, args);
    va_end(args);
    exit(EXIT_FAILURE);
}
