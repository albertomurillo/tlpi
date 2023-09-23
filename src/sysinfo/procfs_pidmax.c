#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/log/log.h"

#define MAX_LINE 100

int main(int argc, char *argv[])
{
    int fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
    if (fd == -1)
        log_fatal("open");

    char line[MAX_LINE];
    ssize_t n = read(fd, line, MAX_LINE);
    if (n == -1)
        log_fatal("read");

    // If no arguments, just print the value and exit
    if (argc == 1) {
        printf("%.*s", (int)n, line);
        exit(EXIT_SUCCESS);
    }

    // If has arguments, print old value, update and print again
    printf("Old value: ");
    printf("%.*s", (int)n, line);

    if (lseek(fd, 0, SEEK_SET) == -1)
        log_fatal("lseek");

    if (write(fd, argv[1], strlen(argv[1]) != strlen(argv[1])))
        log_fatal("write() failed");

    system("echo /proc/sys/kernel/pid_max now contains $(cat /proc/sys/kernel/pid_max)");
    exit(EXIT_SUCCESS);
}
