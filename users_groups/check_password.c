#include <errno.h>
#include <pwd.h>
#include <shadow.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/log/log.h"

int main()
{
    // If limit is indeterminate, make a guess
    long lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if (lnmax == -1)
        lnmax = 256;

    char* username = alloca(lnmax);
    if (username == NULL)
        log_fatal("alloca()");

    printf("Username: ");
    fflush(stdout);

    // Exit on EOF
    if (fgets(username, lnmax, stdin) == NULL)
        log_fatal("fgets()");

    // Remove trailing '\n'
    size_t len = strlen(username);
    if (username[len - 1] == '\n')
        username[len - 1] = '\0';

    struct passwd* pwd = getpwnam(username);
    if (pwd == NULL)
        log_fatal("couldn't get password record");

    struct spwd* spwd = getspnam(username);
    if (spwd == NULL && errno == EACCES)
        log_fatal("no permission to read shadow password file");

    // If there is a shadow password record, use shadow password
    if (spwd != NULL)
        pwd->pw_passwd = spwd->sp_pwdp;

    char* password = getpass("Password: ");

    // Encrypt password and erase cleartext version immediately
    char* encrypted = crypt(password, pwd->pw_passwd);
    memset(password, '\0', lnmax);
    if (encrypted == NULL)
        log_fatal("crypt()");

    bool auth = (strcmp(encrypted, pwd->pw_passwd) == 0);
    if (!auth) {
        printf("Incorrect password\n");
        exit(EXIT_FAILURE);
    }

    printf("successfully authenticated: UID=%ld\n", (long)pwd->pw_uid);
    exit(EXIT_SUCCESS);
}
