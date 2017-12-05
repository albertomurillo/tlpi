#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif

int main(int argc, char **argv) {
  int opt;
  bool append = false;
  char *filename;
  while ((opt = getopt(argc, argv, "a")) != -1) {
    switch (opt) {
    case 'a':
      append = true;
      break;
    default:
      fprintf(stderr, "Usage: %s [-a] [filename]\n", argv[0]);
      return EXIT_FAILURE;
    }
  }
  filename = argv[optind];

  int flags = O_CREAT | O_WRONLY | (append ? O_APPEND : O_TRUNC);
  mode_t mode = S_IRUSR | S_IWUSR | S_IROTH;
  int fd = NULL;
  if (filename) {
    if ((fd = open(filename, flags, mode)) == -1) {
      perror("Unable to open file");
      return EXIT_FAILURE;
    }
  }

  char buff[BUFF_SIZE];
  ssize_t bytesRead;
  ssize_t bytesWritten;
  while ((bytesRead = read(STDIN_FILENO, buff, BUFF_SIZE)) > 0) {
    if ((bytesWritten = write(STDOUT_FILENO, buff, bytesRead)) == -1) {
      perror("Unable to write to stdout");
      return EXIT_FAILURE;
    }
    if (filename) {
      if ((bytesWritten = write(fd, buff, bytesRead)) == -1) {
        perror("Unable to write to filename");
        return EXIT_FAILURE;
      }
    }
  }

  if (fd) {
    close(fd);
  }

  return EXIT_SUCCESS;
}
