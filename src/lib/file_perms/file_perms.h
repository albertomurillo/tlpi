#pragma once

#include <sys/types.h>

// Include set-user-ID, set-group-ID, and sticky bit information in returned strings
#define FP_SPECIAL 1

char *file_perm_str(mode_t perm, int flags);
