#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../lib/log/log.h"

static void fpathconf_print(const char *msg, int fd, int name)
{
    errno = 0;
    long lim = fpathconf(fd, name);

    if (errno != 0)
        log_fatalf("fpathconf %s", msg);

    if (lim == -1) {
        printf("%s (indeterminate)\n", msg);
        return;
    }

    printf("%s %ld\n", msg, lim);
}

int main(int argc, char *argv[])
{
    fpathconf_print("_PC_NAME_MAX: ", STDIN_FILENO, _PC_NAME_MAX);
    fpathconf_print("_PC_PATH_MAX: ", STDIN_FILENO, _PC_PATH_MAX);
    fpathconf_print("_PC_PIPE_BUF: ", STDIN_FILENO, _PC_PIPE_BUF);

    exit(EXIT_SUCCESS);
}
