#include "functions.h"

int main(int argc, char *argv[]) {
  printf("Hello! Welcome to our shell. Type \"exit\" to leave.\n");
  int exit = 1;
  // so that it goes on forever until exited
  while(exit) {
    exit = parse_args(read_args());
    int i, j;
  
    // current problem- if it says exit before last command, it doesn't work
    if (exit == -1) {
      printf("please give a good terminal command\n");
    }

  }
  return 0;
}