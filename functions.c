#include "functions.h"

char ** parse_args(char *line) {
  char **args = calloc(ARG_NUM, sizeof(char *)); 
  args[0] = line; 
  int i;
  for (i = 1; i < ARG_NUM; i++) {
    if (strsep(&line, " ") != NULL) args[i] = line;
  }
  return args;
}

char * read_args() {
  char * input = malloc(100);
  printf("Enter a command for the shell: ");
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = 0; // gets rid of the newline

  return input;
}

int execute_args(char **args) {
  // exit
  if (!strcmp(args[0], "exit")) {
    return 0;
  }
  // cd (LATER)

  // other
  int pid = fork();
  if (!pid) {
    int success = execvp(args[0], args);
    if (success == -1) return -1;
  }
  else {
    int status;
    int pid_stat = wait(&status);
  }
  return 1;
}