#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

static jmp_buf env;

noreturn static void f2()
{
    longjmp(env, 2);
}

noreturn static void f1(int argc)
{
    if (argc == 1)
        longjmp(env, 1);

    f2();
}

int main(int argc, char *argv[])
{
    switch (setjmp(env)) {
    case 0:
        puts("Calling f1() after initial setjmp()");
        f1(argc);
        break;
    case 1:
        puts("We jumped back from f1()");
        break;
    case 2:
        puts("We jumped back from f2()");
        break;
    default:
        break;
    }

    exit(EXIT_SUCCESS);
}
