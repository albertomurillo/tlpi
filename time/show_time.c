#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/log/log.h"

#define BUFF_SIZE 200

int main(int argc, char *argv[])
{
    if (setlocale(LC_ALL, "") == NULL)
        log_fatal("setlocale()");

    time_t t = time(NULL);
    printf("ctime() of time() value is: %s", ctime(&t));

    struct tm *loc = localtime(&t);
    if (loc == NULL)
        log_fatal("localtime()");
    printf("asctime() of local time is %s", asctime(loc));

    char buf[BUFF_SIZE];
    if (strftime(buf, BUFF_SIZE, "%A, %d %B %Y, %H:%M:%S %Z", loc) == 0)
        log_fatal("strftime() returned 0");

    printf("strftime() of local time is %s\n", buf);

    exit(EXIT_SUCCESS);
}
