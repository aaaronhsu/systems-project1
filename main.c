#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

// for now the max args it takes is 5 if you input during the prompt
#define ARG_NUM 5

char ** parse_args(char *line);

int main(int argc, char *argv[]) {
  // argc - 1 is the amount of args in command line
  char ** args = calloc(ARG_NUM, sizeof(char *));
  if (argc >= 2) {
    // you have the args now loop through and add them
    int i;
    for (int i = 1; i < ARG_NUM; i++) {
      args[i - 1] = argv[i];
    }
  } else {
    char input[100];
    printf("Enter a command for the shell: ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0; // gets rid of the newline
    args = parse_args(input);
  }

  // test the two methods of assigning args
  for (int i = 0; i < ARG_NUM; i++) {
    printf("%s\n", args[i]);
  }

  return 0;
}

char ** parse_args(char *line) {
  char **args = calloc(ARG_NUM, sizeof(char *)); 
  args[0] = line; 
  int i;
  for (int i = 1; i < ARG_NUM; i++) {
    if (strsep(&line, " ") != NULL) args[i] = line;
  }
  return args;
}
 
