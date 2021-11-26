#include "functions.h"

// ISSUE: strsep only separates by spaces so there have to be spaces around each semicolon
// ALSO: doesn't work when you add an access space at the end
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

int semi_exec(char ** args) {
  int i, j, exit;
  int start = 0;
  int semi_last = 0; // assume last one isn't semi
  char ** args1;
  char ** args2;

  for (i = 0; i < ARG_NUM - 1; i++) {
    if (args[i] == NULL) {
      if (*args[i - 1] == ';') semi_last = 1;
      break;
    }
    if (*args[i] == ';') {
      args1 = calloc(i - start, sizeof(char *));
      for (j = i - 1; j >= start; j--) {
        // if there are terminating spaces, ignore them
        if (*args[j] == ' ') continue;
        args1[j - start] = args[j];
      }

      exit = execute_args(args1);
      // just like in terminal, say command not found for just that one
      if (exit == -1){
        print_command_not_found(args1);
      }
      start = i + 1;
    }
  }
  if (!semi_last) { // last one isn't semi
    args1 = calloc(ARG_NUM, sizeof(char *)); // calloc too much space bc idk how to find actual amount
    for (i = start; i < ARG_NUM; i++) {
      args1[i - start] = args[i];
    }
    exit = execute_args(args1);
    // current problem- if it says exit before last command, it doesn't work
    if (exit == -1) {
      print_command_not_found(args1);
    }
  }
    return exit;
}

int execute_args(char **args) {
  // count the number of args for later
  int arg_count = 0;
  while (args[arg_count] != NULL) {
    arg_count++;
  }

  // exit
  if (!strcmp(args[0], "exit")) {
    exit(0); // does this just exit wherever?
    return 0;
  }
  // cd
  else if (!strcmp(args[0], "cd")) {
    if (arg_count != 2) printf("format using cd [path/to/dir]\n");
    else {
      int status = chdir(args[1]);
      if (status == -1) printf("failed to change directories: %s\n", strerror(errno));
    }
    // returns 1 even though it didn't work because we don't also need the automated error message
    return 1;
  }
  // other
  else {
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
}