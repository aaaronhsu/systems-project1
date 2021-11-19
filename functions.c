#include "functions.h"

char ** parse_args(char *line) {
  char **args = calloc(ARG_NUM, sizeof(char *)); 
  args[0] = line; 
  int i;
  for (i = 1; i < ARG_NUM; i++) {
    if (strsep(&line, " ") != NULL) args[i] = line;
  }


  // TODO: edge case- if you put a space as the last arg it takes up a slot
  
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
  if (!strcmp(args[0], "exit")) {
    return 0;
  }
  return 1;
}