#define _GNU_SOURCE

#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <unistd.h>

#include "../lib/getnum/getnum.h"
#include "../lib/log/log.h"

noreturn static void usage(char *name)
{
    fprintf(stderr, "Usage: %s <file> <length> [offset [alignment]]\n", name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usage(argv[0]);

    size_t length = get_long(argv[2]);
    off_t offset = (argc > 3) ? get_long(argv[3]) : 0;
    size_t alignment = (argc > 4) ? get_long(argv[4]) : 4096;

    int fd = open(argv[1], O_RDONLY | O_DIRECT);
    if (fd == -1)
        log_fatale("open()");

    // memalign() allocates a block of memory aligned on an address that
    // is a multiple of its first argument.
    //
    // By specifying this argument as 2 * 'alignment'
    // and then adding 'alignment' to the returned pointer,
    // we ensure that 'buf' is aligned on a non-power-of-two multiple of 'alignment'.
    //
    // We do this to ensure that if, for example, we ask
    // for a 256-byte aligned buffer, we don't accidentally get a
    // buffer that is also aligned on a 512-byte boundary.
    char *buf = memalign(alignment * 2, length + alignment);
    if (buf == NULL)
        log_fatale("memalign()");

    buf += alignment;

    if (lseek(fd, offset, SEEK_SET) == -1)
        log_fatale("lseek()");

    ssize_t num_read = read(fd, buf, length);
    if (num_read == -1)
        log_fatale("read()");
    printf("read %ld bytes\n", num_read);

    exit(EXIT_SUCCESS);
}
