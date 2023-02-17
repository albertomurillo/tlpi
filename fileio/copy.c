#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../lib/log/log.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char* argv[])
{
    // check usage
    if (argc != 3) {
        fprintf(stderr, "usage: %s source_file target_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // open input file
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        log_fatalf("opening file %s: %s\n", argv[1], strerror(errno));
    }

    // open output file
    int dest_flags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t dest_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int dest_fd = open(argv[2], dest_flags, dest_perms);
    if (dest_fd == -1) {
        log_fatalf("opening file %s: %s\n", argv[2], strerror(errno));
    }

    // copy from input file to output file
    char buf[BUF_SIZE];
    ssize_t n;
    while ((n = read(src_fd, buf, BUF_SIZE)) > 0) {
        if ((write(dest_fd, buf, n)) != n) {
            log_fatalf("writing file %s\n", argv[2]);
        }
    }
    if (n == -1) {
        log_fatalf("reading file %s\n", argv[1]);
    }

    // close output file
    if (close(dest_fd) == -1) {
        log_fatalf("closing file %s\n", argv[2]);
    }

    // close input file
    if (close(src_fd) == -1) {
        log_fatalf("closing file %s\n", argv[1]);
    }

    exit(EXIT_SUCCESS);
}
