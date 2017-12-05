#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char *filename = argv[1];
  int flags = O_CREAT | O_APPEND | O_WRONLY;
  mode_t mode = S_IRUSR | S_IWUSR | S_IROTH;

  int fd;
  if ((fd = open(filename, flags, mode)) == -1) {
    perror("Unable to open file");
    return EXIT_FAILURE;
  }

  off_t offset;
  offset = lseek(fd, 0, SEEK_SET);

  ssize_t n;
  if (n = write(fd, filename, strlen(filename)) != strlen(filename)) {
    perror("Unable to write to file");
    return EXIT_FAILURE;
  }

  close(fd);
  return EXIT_SUCCESS;
}
