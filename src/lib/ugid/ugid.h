#pragma once

#include <grp.h>
#include <pwd.h>

char *user_name_from_id(const uid_t uid);
uid_t user_id_from_name(const char *name);

char *group_name_from_uid(const uid_t uid);
gid_t group_id_from_name(const char *name);
