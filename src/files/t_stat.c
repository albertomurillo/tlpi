#define _DEFAULT_SOURCE

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

#include "../lib/file_perms/file_perms.h"
#include "../lib/log/log.h"

typedef int (*fn_stat_t)(const char *, struct stat *);

noreturn static void usage(const char *prog)
{
    fprintf(stderr, "Usage: %s [OPTIONS] file\n", prog);
    fprintf(stderr, "\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -l              use lstat() instead of stat()\n");
    exit(EXIT_FAILURE);
}

static void display_stat_info(const struct stat *sb)
{
    const char *f_type = NULL;
    switch (sb->st_mode & S_IFMT) {
    case S_IFREG: f_type = "regular file"; break;
    case S_IFDIR: f_type = "directory"; break;
    case S_IFCHR: f_type = "character device"; break;
    case S_IFBLK: f_type = "block device"; break;
    case S_IFLNK: f_type = "symbolic (soft) link"; break;
    case S_IFIFO: f_type = "FIFO or pipe"; break;
    case S_IFSOCK: f_type = "socket"; break;
    default: f_type = "unknown file type"; break;
    }
    printf("File type:                %s\n", f_type);
    printf("Device containing i-node: major=%ld    minor=%ld\n", (long)major(sb->st_dev), (long)minor(sb->st_dev));
    printf("I-node number:            %ld\n", (long)sb->st_ino);
    printf("Mode:                     %lo (%s)\n", (long)sb->st_mode, file_perm_str(sb->st_mode, 0));
    if (sb->st_mode & (S_ISUID | S_ISGID | S_ISVTX))
        printf("    special bits set: %s%s%s\n",
            (sb->st_mode & S_ISUID) ? "    set-UID " : "",
            (sb->st_mode & S_ISGID) ? "    set-GID " : "",
            (sb->st_mode & S_ISVTX) ? "    sticky " : "");
    printf("Number of (hard) links:   %ld\n", (long)sb->st_nlink);
    printf("Ownership:                UID=%ld    GID=%ld\n", (long)sb->st_uid, (long)sb->st_gid);
    if (S_ISCHR(sb->st_mode) || S_ISBLK(sb->st_mode))
        printf("Device number (st_rddev): major=%ld    minor=%ld\n", (long)major(sb->st_rdev), (long)minor(sb->st_rdev));
    printf("File size:                %lld bytes\n", (long long)sb->st_size);
    printf("Optimal I/O block size:   %ld bytes\n", sb->st_blksize);
    printf("512B blocks allocated:    %lld\n", (long long)sb->st_blocks);
    printf("Last file access:         %s", ctime(&sb->st_atime));
    printf("Last file modification:   %s", ctime(&sb->st_mtime));
    printf("Last status change:       %s", ctime(&sb->st_ctime));
}

int main(int argc, char *argv[])
{
    fn_stat_t fn_stat = &stat;
    const char *fn_state_name = "stat()";
    const char *file_name = NULL;

    int opt = 0;
    while ((opt = getopt(argc, argv, "l")) != -1) {
        switch (opt) {
        case 'l':
            fn_stat = &lstat;
            fn_state_name = "lstat()";
            break;
        case 'h': usage(argv[0]); break;
        default: usage(argv[0]);
        }
    }
    if (argc != optind + 1)
        usage(argv[0]);
    file_name = argv[optind];

    struct stat sb;
    if (fn_stat(file_name, &sb) == -1)
        log_fatale(fn_state_name);
    display_stat_info(&sb);

    exit(EXIT_SUCCESS);
}
