#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

#include "file_perms.h"

#define STR_SIZE sizeof("rwxrwxrwx")

char *file_perm_str(mode_t perm, int flags)
{
    static char str[STR_SIZE];
    bool sticky = false;
    char *ptr = str;

    sticky = ((perm & S_ISUID) && (flags & FP_SPECIAL));
    *ptr++ = (perm & S_IRUSR) ? 'r' : '-';
    *ptr++ = (perm & S_IWUSR) ? 'w' : '-';
    *ptr++ = (perm & S_IXUSR) ? (sticky ? 's' : 'x') : (sticky ? 'S' : '-');

    sticky = ((perm & S_ISGID) && (flags & FP_SPECIAL));
    *ptr++ = (perm & S_IRGRP) ? 'r' : '-';
    *ptr++ = (perm & S_IWGRP) ? 'w' : '-';
    *ptr++ = (perm & S_IXGRP) ? (sticky ? 's' : 'x') : (sticky ? 'S' : '-');

    sticky = ((perm & S_ISVTX) && (flags & FP_SPECIAL));
    *ptr++ = (perm & S_IROTH) ? 'r' : '-';
    *ptr++ = (perm & S_IWOTH) ? 'w' : '-';
    *ptr++ = (perm & S_IXOTH) ? (sticky ? 't' : 'x') : (sticky ? 'T' : '-');

    *ptr++ = '\0';
    return str;
}
