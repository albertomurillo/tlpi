#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/reboot.h>
#include <unistd.h>

bool is_root(uid_t uid) { return uid == 0; }

int main() {
  uid_t uid;
  uid = getuid();

  if (!is_root(uid)) {
    fprintf(stderr, "This program must be run as root.\n");
    return EXIT_FAILURE;
  }

  reboot(RB_AUTOBOOT);

  return EXIT_SUCCESS;
}
