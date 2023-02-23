#define _GNU_SOURCE

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/env/env.h"
#include "../lib/log/log.h"

extern char **environ;

int main(int argc, char *argv[])
{
    clearenv();

    for (int i = 1; i < argc; i++)
        if (putenv(argv[i]) != 0)
            log_fatalf("putenv: %s\n", argv[i]);

    if (setenv("GREET", "Hello world", false) == -1)
        log_fatalf("setenv: %s\n", strerror(errno));

    unsetenv("BYE");

    for (char **ep = environ; *ep != NULL; ep++)
        puts(*ep);

    exit(EXIT_SUCCESS);
}
