#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "log.h"

void usage(char* name)
{
    fprintf(stderr, "usage: %s file [r<length> | R<length> | w<string> | s<offset>]\n", name);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    // Usage
    if (argc < 3) {
        usage(argv[0]);
    }

    // Open file
    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        log_fatalf("opening file %s: %s\n", argv[1], strerror(errno));
    }

    // Parse options
    for (int ap = 2; ap < argc; ap++) {
        switch (argv[ap][0]) {
        case 'r': // Display bytes at current offset, as text
        case 'R': // Display bytes at current offset, in hex
        {
            errno = 0;
            char* eptr;
            size_t len = strtol(&argv[ap][1], &eptr, 10);
            if (errno != 0) {
                log_fatalf("%s: %s\n", argv[ap], strerror(errno));
            }

            unsigned char* buf = malloc(len);
            if (buf == NULL) {
                log_fatalf("malloc: %s\n", strerror(errno));
            }

            size_t n = read(fd, buf, len);
            if (n == -1) {
                log_fatalf("read: %s\n", strerror(errno));
            }
            if (n == 0) {
                printf("%s: end-of-file\n", argv[ap]);
            } else {
                printf("%s: ", argv[ap]);
                for (int i = 0; i < n; i++) {
                    if (argv[ap][0] == 'r') {
                        printf("%c", isprint(buf[i]) ? buf[i] : '?');
                    } else {
                        printf("%02x ", buf[i]);
                    }
                }
                printf("\n");
            }

            free(buf);
            break;
        }

        case 'w': // Write string at current offset
        {
            char* val = &argv[ap][1];
            size_t n = write(fd, val, strlen(val));
            if (n == -1) {
                log_fatalf("writing to file %s: %s", argv[1], strerror(errno));
            }
            printf("%s: wrote %ld bytes\n", argv[ap], n);
            break;
        }

        case 's': // Change file offset
        {
            errno = 0;
            char* eptr;
            ssize_t offset = strtol(&argv[ap][1], &eptr, 10);
            if (errno != 0) {
                log_fatalf("%s: %s\n", argv[ap], strerror(errno));
            }

            if (lseek(fd, offset, SEEK_SET) == -1) {
                log_fatalf("lseek: %s\n", strerror(errno));
            }

            printf("%s: lseek succeeded\n", argv[ap]);
            break;
        }

        default:
            usage(argv[0]);
        }
    }

    exit(EXIT_SUCCESS);
}
