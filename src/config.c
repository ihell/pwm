#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void launch() {
  const char *home_dir = getenv("HOME");
  if (!home_dir) {
    fprintf(stderr, "Failed to find home directory\n");
    exit(1);
  }

  char sxhkdrc_path[512];
  snprintf(sxhkdrc_path, sizeof(sxhkdrc_path), "%s/.config/sxhkd/sxhkdrc",
           home_dir);

  if (access(sxhkdrc_path, F_OK) == -1) {
    fprintf(stderr, "sxhkdrc file not found at: %s\n", sxhkdrc_path);
    exit(1);
  }

  if (fork() == 0) {
    char command[1024];

    snprintf(command, sizeof(command), "sxhkd -c %s &", sxhkdrc_path);
    int status = system(command);
    if (status == -1) {
      perror("Failed to launch sxhkd");
      exit(1);
    }

    snprintf(command, sizeof(command), "nitrogen --restore &");
    status = system(command);
    if (status == -1) {
      perror("Failed to launch nitrogen");
      exit(1);
    }

    snprintf(command, sizeof(command), "nitrogen --fill &");
    status = system(command);
    if (status == -1) {
      perror("Failed to launch nitrogen");
      exit(1);
    }

    exit(0);
  }
}
