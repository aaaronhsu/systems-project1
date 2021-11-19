#include "functions.h"

int main(int argc, char *argv[]) {
  printf("Hello! Welcome to our shell. Type \"exit\" to leave.\n");
  int exit = 1;
  char ** args = calloc(ARG_NUM, sizeof(char *));
  // so that it goes on forever until exited
  while(exit) {
    args = parse_args(read_args());

    // TESTING the two methods of assigning args
    for (int i = 0; i < ARG_NUM; i++) {
      printf("%s\n", args[i]);
    }

    exit = execute_args(args);
    if (exit == -1) {
      printf("please give a good terminal command\n");
    }

  }
  return 0;
}