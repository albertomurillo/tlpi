#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../lib/log/log.h"

static void sysconf_print(const char *msg, int name)
{
    errno = 0;
    long lim = sysconf(name);

    if (errno != 0)
        log_fatalf("sysconf %s", msg);

    if (lim == -1) {
        printf("%s (indeterminate)\n", msg);
        return;
    }

    printf("%s %ld\n", msg, lim);
}

int main(int argc, char *argv[])
{
    sysconf_print("_SC_ARG_MAX:        ", _SC_ARG_MAX);
    sysconf_print("_SC_LOGIN_NAME_MAX: ", _SC_LOGIN_NAME_MAX);
    sysconf_print("_SC_OPEN_MAX:       ", _SC_OPEN_MAX);
    sysconf_print("_SC_NGROUPS_MAX:    ", _SC_NGROUPS_MAX);
    sysconf_print("_SC_PAGESIZE:       ", _SC_PAGESIZE);
    sysconf_print("_SC_RTSIG_MAX:      ", _SC_RTSIG_MAX);

    exit(EXIT_SUCCESS);
}
