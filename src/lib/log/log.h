#ifndef LOG_H
#define LOG_H

#include <stdnoreturn.h>

noreturn void log_fatal(const char *msg);
noreturn void log_fatalf(const char *format, ...);

#endif // LOG_H
