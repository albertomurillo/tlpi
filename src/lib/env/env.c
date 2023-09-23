#ifdef __APPLE__

#include <stdlib.h>
#include <string.h>

extern char **environ;

void clearenv()
{
    for (char **ep = environ; *ep != NULL;) {
        size_t len = strlen(*ep);
        char buf[len];
        strcpy(buf, *ep);
        char *envvar = strtok(buf, "=");
        unsetenv(envvar);
    }
}

#endif // __APPLE__
