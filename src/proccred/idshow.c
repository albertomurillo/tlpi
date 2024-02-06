#define _GNU_SOURCE

#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fsuid.h>
#include <unistd.h>

#include "../lib/log/log.h"
#include "../lib/ugid/ugid.h"

#define SG_SIZE (NGROUPS_MAX + 1)

int main(int argc, char *argv[])
{
    uid_t ruid;
    uid_t euid;
    uid_t suid;
    if (getresuid(&ruid, &euid, &suid) == -1)
        log_fatal("getresuid()");

    gid_t rgid;
    gid_t egid;
    gid_t sgid;
    if (getresgid(&rgid, &egid, &sgid) == -1)
        log_fatal("getresgid()");

    // Attempts to change the file-system IDs are always ignored
    // for unprivileged processes, but even so, the following
    // calls return the current file-system IDs
    uid_t fsuid = setfsuid(0);
    gid_t fsgid = setfsgid(0);

    char *p;
    printf("UID: ");
    p = user_name_from_id(ruid);
    printf("real=%s (%d); ", (p == NULL) ? "???" : p, ruid);
    p = user_name_from_id(euid);
    printf("effective=%s (%d); ", (p == NULL) ? "???" : p, euid);
    p = user_name_from_id(suid);
    printf("saved=%s (%d); ", (p == NULL) ? "???" : p, suid);
    p = user_name_from_id(fsuid);
    printf("fs=%s (%d); ", (p == NULL) ? "???" : p, fsuid);
    printf("\n");

    printf("GID: ");
    p = group_name_from_uid(rgid);
    printf("real=%s (%d); ", (p == NULL) ? "???" : p, rgid);
    p = group_name_from_uid(egid);
    printf("effective=%s (%d); ", (p == NULL) ? "???" : p, egid);
    p = group_name_from_uid(sgid);
    printf("saved=%s (%d); ", (p == NULL) ? "???" : p, sgid);
    p = group_name_from_uid(fsgid);
    printf("fs=%s (%d); ", (p == NULL) ? "???" : p, fsgid);
    printf("\n");

    gid_t supplementary_groups[SG_SIZE];
    int num_groups = getgroups(SG_SIZE, supplementary_groups);
    if (num_groups == -1)
        log_fatal("getgroups()");
    printf("supplementary groups (%d): ", num_groups);
    for (int j = 0; j < num_groups; j++) {
        p = group_name_from_uid(supplementary_groups[j]);
        printf("%s (%d) ", (p == NULL) ? "???" : p, supplementary_groups[j]);
    }
    printf("\n");

    exit(EXIT_SUCCESS);
}
