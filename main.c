#include "functions.h"

int main(int argc, char *argv[]) {
  printf("Hello! Welcome to our shell. Type \"exit\" to leave and note that all items on the command line must be separated by a space.\n");
  int exit = 1;
  char ** args = calloc(ARG_NUM, sizeof(char *));
  // keeps track of how many times the loop has been used 
  int session = 0;
  // so that it goes on forever until exited
  while(exit) {
    args = parse_args(read_args(), session);
    // doesn't actually matter what exit is because exit(0) quits everything and the -1 doesn't affect loop
    exit = semi_exec(args);
    session++;

  }
  return 0;
}