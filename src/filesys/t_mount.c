#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>

#include "../lib/log/log.h"

static void usage(const char *prog)
{
    fprintf(stderr, "Usage: %s [OPTIONS] source target\n", prog);
    fprintf(stderr, "\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -t fstype       e.g., 'ext2' or 'reiserfs'\n");
    fprintf(stderr, "  -o data         file system-dependent options,\n");
    fprintf(stderr, "                  e.g., 'bsdgroups' for ext2\n");
    fprintf(stderr, "  -f mountflags   can include any of:\n");
    fprintf(stderr, "                    b - MS_BIND         create a bind mount\n");
    fprintf(stderr, "                    d - MS_DIRSYNC      synchronous directory updates\n");
    fprintf(stderr, "                    l - MS_MANDLOCK     permit mandatory locking\n");
    fprintf(stderr, "                    m - MS_MOVE         atomically move subtree\n");
    fprintf(stderr, "                    A - MS_NOATIME      don't update atime (last access time)\n");
    fprintf(stderr, "                    V - MS_NODEV        don't permit device access\n");
    fprintf(stderr, "                    D - MS_NODIRATIME   don't update atime on directories\n");
    fprintf(stderr, "                    E - MS_NOEXEC       don't allow executables\n");
    fprintf(stderr, "                    S - MS_NOSUID       disable set-user/group-ID programs\n");
    fprintf(stderr, "                    r - MS_RDONLY       read-only mount\n");
    fprintf(stderr, "                    c - MS_REC          recursive mount\n");
    fprintf(stderr, "                    R - MS_REMOUNT      remount\n");
    fprintf(stderr, "                    s - MS_SYNCHRONOUS  make writes synchronous\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    unsigned long flags = 0;
    int opt = 0;
    const char *data = NULL;
    const char *fstype = NULL;

    while ((opt = getopt(argc, argv, "o:t:f:")) != -1) {
        switch (opt) {
        case 'o': data = optarg; break;
        case 't': fstype = optarg; break;
        case 'f':
            for (int i = 0; i < strlen(optarg); i++) {
                switch (optarg[i]) {
                case 'b': flags |= MS_BIND; break;
                case 'd': flags |= MS_DIRSYNC; break;
                case 'l': flags |= MS_MANDLOCK; break;
                case 'm': flags |= MS_MOVE; break;
                case 'A': flags |= MS_NOATIME; break;
                case 'V': flags |= MS_NODEV; break;
                case 'D': flags |= MS_NODIRATIME; break;
                case 'E': flags |= MS_NOEXEC; break;
                case 'S': flags |= MS_NOSUID; break;
                case 'r': flags |= MS_RDONLY; break;
                case 'c': flags |= MS_REC; break;
                case 'R': flags |= MS_REMOUNT; break;
                case 's': flags |= MS_SYNCHRONOUS; break;
                default: usage(argv[0]);
                }
            }
            break;

        default: usage(argv[0]);
        }
    }

    if (argc != optind + 2)
        usage(argv[0]);

    if (mount(argv[optind], argv[optind + 1], fstype, flags, data) == -1)
        log_fatal("mount");

    exit(EXIT_SUCCESS);
}
