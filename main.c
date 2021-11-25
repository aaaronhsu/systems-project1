#include "functions.h"

int main(int argc, char *argv[]) {
  printf("Hello! Welcome to our shell. Type \"exit\" to leave.\n");
  int exit = 1;
  char ** args = calloc(ARG_NUM, sizeof(char *));
  // so that it goes on forever until exited
  while(exit) {
    args = parse_args(read_args());
    int i, j;

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

  }
  return 0;
}