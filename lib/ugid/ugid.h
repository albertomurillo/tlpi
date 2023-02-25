#ifndef UGID_H
#define UGID_H

#include <grp.h>
#include <pwd.h>

char *user_name_from_id(uid_t uid);
uid_t user_id_from_name(const char *name);

char *group_name_from_uid(uid_t uid);
gid_t group_id_from_name(const char *name);

#endif // UGID_H
