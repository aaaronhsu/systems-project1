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
  } else {
    char input[100];
    printf("Enter a command for the shell: ");
    fgets(input, 100, stdin);
    sscanf(input, "%s", input);
    // copy parse args function
  }


  printf("Here is the input: %s\n", input);

  return 0;
}
