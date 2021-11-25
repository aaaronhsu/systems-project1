#include "functions.h"

int main(int argc, char *argv[]) {
  printf("Hello! Welcome to our shell. Type \"exit\" to leave.\n");
  int exit = 1;
  char ** args = calloc(ARG_NUM, sizeof(char *));
  // so that it goes on forever until exited
  while(exit) {
    args = parse_args(read_args());
    // doesn't actually matter what exit is because exit(0) quits everything and the -1 doesn't affect loop
    exit = semi_exec(args);
    

  }
  return 0;
}