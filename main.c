#include "headers.h"

// for now the max args it takes is 5 if you input during the prompt
#define ARG_NUM 5

char ** parse_args(char *line);

int main(int argc, char *argv[]) {
  int exit = 1;
  printf("Hello! Welcome to our shell. Type \"exit\" to leave.\n");
  // for command line input if it exists
  char ** args = calloc(ARG_NUM, sizeof(char *));
  if (argc >= 2) {
      // you have the args now loop through and add them
      int i;
      for (int i = 1; i < ARG_NUM; i++) {
        args[i - 1] = argv[i];
      }
  }
  // so that it goes on forever until exited
  while(exit) {
    args = calloc(ARG_NUM, sizeof(char *));
    char input[100];
    printf("Enter a command for the shell: ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0; // gets rid of the newline
    args = parse_args(input);

    // TESTING the two methods of assigning args
    for (int i = 0; i < ARG_NUM; i++) {
      printf("%s\n", args[i]);
    }
    // exit function 
    if (!strcmp(args[0], "exit")) {
      exit = 0;
    }
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
  // TODO: edge case- if you put a space as the last arg it takes up a slot
  return args;
}
 
