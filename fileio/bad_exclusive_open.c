#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "log.h"

int main(int argc, char* argv[])
{
    const int SLEEP_TIME = 5;
    pid_t pid = getpid();
    char* filename = argv[1];
    int flags = O_WRONLY;

    // check usage
    if (argc != 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // check if file exists
    int fd = open(argv[1], flags);
    if (fd != -1) {
        log_fatalf("[PID %d] file \"%s\" already exists\n", pid, filename);
    }

    // failed for unexpected reason
    if (errno != ENOENT) {
        log_fatalf("[PID %d] file \"%s\" %s\n", pid, filename, strerror(errno));
    }

    // WINDOW FOR FAILURE
    printf("[PID %d] file \"%s\" doesn't exist yet\n", pid, filename);
    printf("[PID %d] sleeping for %d seconds\n", pid, SLEEP_TIME);
    sleep(SLEEP_TIME);
    printf("[PID %d] done sleeping\n", pid);

    fd = open(argv[1], flags | O_CREAT, 0600);
    if (fd == -1) {
        log_fatalf("[PID %d] file \"%s\" %s\n", pid, filename, strerror(errno));
    }
    printf("[PID %d] created file \"%s\" exclusively\n", pid, filename);
    exit(EXIT_SUCCESS);
}
