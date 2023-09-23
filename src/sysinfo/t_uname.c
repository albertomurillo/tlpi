#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

#include "../lib/log/log.h"

int main(int agrc, char *argv[])
{
    struct utsname uts;

    if (uname(&uts) == -1)
        log_fatal("uname");

    printf("Node name: %s\n", uts.nodename);
    printf("System name: %s\n", uts.sysname);
    printf("Release: %s\n", uts.release);
    printf("Version: %s\n", uts.version);
    printf("Machine: %s\n", uts.machine);

#ifndef __APPLE__
#ifdef _GNU_SOURCE
    printf("Domain name: %s\n", uts.domainname);
#endif
#endif

    exit(EXIT_SUCCESS);
}
