#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>

#include "ugid.h"

char *user_name_from_id(const uid_t uid)
{
    const struct passwd *const pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

uid_t user_id_from_name(const char *name)
{
    if (name == NULL || *name == '\0')
        return -1;

    const struct passwd *const pwd = getpwnam(name);
    return (pwd == NULL) ? -1 : pwd->pw_uid;
}

char *group_name_from_uid(const uid_t uid)
{
    const struct group *const grp = getgrgid(uid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t group_id_from_name(const char *name)
{
    if (name == NULL || *name == '\0')
        return -1;

    const struct group *const grp = getgrnam(name);
    return (grp == NULL) ? -1 : grp->gr_gid;
}
