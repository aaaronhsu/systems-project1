#include "functions.h"

// ISSUE: strsep only separates by spaces so there have to be spaces around each semicolon
char ** parse_args(char *line) {
  char **args = calloc(ARG_NUM, sizeof(char *)); 
  args[0] = line; 
  int i;
  for (i = 1; i < ARG_NUM; i++) {
    // SEE ISSUE ABOVE- add some if statement here that checks for semis
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

void print_command_not_found(char ** args) {
  printf("command not found: ");
  int i = 0;
  while (args[i] != NULL) {
    printf("%s ", args[i]);
    i++;
  }
  printf("\n");
}

int execute_args(char **args) {
  // exit
  if (!strcmp(args[0], "exit")) {
    exit(0); // does this just exit wherever?
    return 0;
  }
  // cd


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