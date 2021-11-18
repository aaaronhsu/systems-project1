#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  // argc - 1 is the amount of args in command line
  char ** args = calloc(argc - 1, sizeof(char *));
  if (argc >= 2) {
    // you have the args now loop through and add them
    int i;
    for (int i = 1; i < argc; i++) {
      args[i - 1] = argv[i];
    }
  } else {
    char input[100];
    printf("Enter a command for the shell: ");
    fgets(input, 100, stdin);
    printf("input: %s\n", input);
  }

  return 0;
}
