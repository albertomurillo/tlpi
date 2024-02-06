#pragma once

#include <stdnoreturn.h>

noreturn void log_fatal(const char *msg);
noreturn void log_fatale(const char *msg);
noreturn void log_fatalf(const char *format, ...);
