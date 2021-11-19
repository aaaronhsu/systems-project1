#include "functions.h"

int main(int argc, char *argv[]) {
  printf("Hello! Welcome to our shell. Type \"exit\" to leave.\n");
  int exit = 1;
  char ** args = calloc(ARG_NUM, sizeof(char *));
  // so that it goes on forever until exited
  while(exit) {
    args = parse_args(read_args());
    int i, j;
    // TESTING the two methods of assigning args
    for (i = 0; i < ARG_NUM; i++) {
      printf("%s\n", args[i]);
    }

    char ** args1;
    for (i = 0; i < ARG_NUM; i++) {
      if (!strcmp(args[i], ";")) {
        args1 = calloc(i, sizeof(char *));
        for (j = 0; j < i; j++) {
          args1[j] = args[j];
        }
        exit = execute_args(args1);
        if (exit == -1) {
          break;
        }
      }
    }
    exit = execute_args(args1);

    if (exit == -1) {
      printf("please give a good terminal command\n");
    }

  }
  return 0;
}