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
  for (i = 0; i < ARG_NUM - 1; i++) {
    if (args[i] == NULL) {
      if (*args[i - 1] == ';') semi_last = 1;
      break;
    }
    if (*args[i] == ';') {
      args1 = calloc(i - start, sizeof(char *));
      for (j = start; j < i; j++) {
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
  int contains_greater = -1; // >
  int contains_less = -1; // <

  while (args[arg_count] != NULL) {

    // scan for > and <
    if (strcmp(args[arg_count], ">") == 0) contains_greater = arg_count;
    if (strcmp(args[arg_count], "<") == 0) contains_less = arg_count;
    
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

    // creates backup of stdout and stdin so we can restore them later
    int out, in;
    int backup_sdout = dup(STDOUT_FILENO);
    int backup_sdin = dup(STDIN_FILENO);

    if (contains_greater != -1) {
      // >

      // creates file to write to
      out = open(args[contains_greater + 1], O_WRONLY | O_CREAT, 0644);

      // makes the command stop at the >
      args[contains_greater] = '\0';

      // redirects stdout to the file
      dup2(out, STDOUT_FILENO);
    }
    else if (contains_less != -1) {
      // <

      // creates file to read from
      in = open(args[contains_less + 1], O_RDONLY);

      // makes the command stop at the <
      args[contains_less] = '\0';

      // redirects stdin to the file
      dup2(in, STDIN_FILENO);
    }


    int pid = fork();
    if (!pid) {
      int success = execvp(args[0], args);

      // restore stdout and stdin so that the shell can continue
      dup2(backup_sdout, STDOUT_FILENO);
      dup2(backup_sdin, STDIN_FILENO);

      if (success == -1) return -1;
    }
    else {
      int status;
      int pid_stat = wait(&status);
    }

    // restore stdout and stdin so that the shell can continue
    dup2(backup_sdout, STDOUT_FILENO);
    dup2(backup_sdin, STDIN_FILENO);

    return 1;
  }
}