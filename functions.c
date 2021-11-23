#include "functions.h"

int parse_args(char *line) {
  printf("parse_args\n");
  int semi = count_semi(line);

  int i;
  for (i = 0; i < ARG_NUM; i++) {
    if (line[i] == ';') {
      line[i] = '\0';
      printf("replaced %s\n", line[i]);
    }
  }

  int exit = 1;
  char ** to_exec = parse_command(line);
  execute_args(to_exec);

  // THIS LOOP ONLY WORKS ONCE FOR SOME REASON
  for (i = 0; i < ARG_NUM; i++) {
    if ((line[i] == '\0') && semi > 0) {
      exit = execute_args(parse_command(&line[i + 1]));

      if (exit != 1) return exit;
      semi--;
    }
  }

  return exit;
  
}

char ** parse_command(char *line) {
  printf("parse command: %s\n", line);
  int i;
  char **args = calloc(ARG_NUM, sizeof(char *)); 
  args[0] = line; 
  printf("args 0: %s\n", args[0]);
  for (i = 1; i < ARG_NUM; i++) {
    if (strsep(&line, " ") != NULL) args[i] = line;
  }
  return args;
}

int count_semi(char *line) {
  int i = 0;
  int count = 0;
  while (line[count] != '\0') {
    if (line[count] == ';' && (line[count + 1] != NULL)) i++;
    count++;
  }
  printf("semi count: %d\n", i);
  return i;
}



char * read_args() {
  char * input = malloc(100);
  printf("Enter a command for the shell: ");
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = 0; // gets rid of the newline

  return input;
}

int execute_args(char **args) {
  printf("made it to execute args. args[0] = %s\n", args[0]);
  // exit
  if (!strcmp(args[0], "exit")) {
    return 0;
  }
  // cd (LATER)

  // other
  int pid = fork();
  if (!pid) {
    printf("before exec\n");
    int success = execvp(args[0], args);
    if (success == -1) return -1;
  }
  else {
    int status;
    int pid_stat = wait(&status);
  }
  printf("finished exec\n");
  return 1;
}