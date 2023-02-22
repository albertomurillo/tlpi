#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>

#include "../lib/log/log.h"

#ifndef STR_SIZE
#define STR_SIZE 100
#endif

int main(int argc, char* argv[])
{
    // check usage
    if (argc != 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        log_fatalf("%s: %s\n", argv[1], strerror(errno));
    }

    struct iovec iov[3];
    size_t iov_size = 0;

    // first buffer
    struct stat my_struct;
    iov[0].iov_base = &my_struct;
    iov[0].iov_len = sizeof(struct stat);
    iov_size += iov[0].iov_len;

    // second buffer
    int x;
    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    iov_size += iov[1].iov_len;

    // third buffer
    char str[STR_SIZE];
    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    iov_size += iov[2].iov_len;

    ssize_t n = readv(fd, iov, 3);
    if (n == -1) {
        log_fatalf("readv(): %s\n", strerror(errno));
    }
    if (n < iov_size) {
        printf("read fewer bytes than requested\n");
    }
    printf("total bytes requested: %ld; bytes read: %ld\n", iov_size, n);

    exit(EXIT_SUCCESS);
}
