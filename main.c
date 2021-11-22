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
    int start = 0;
    printf("%d\n", ARG_NUM);
    for (i = 0; i < ARG_NUM; i++) {
      printf("round %s\n", args[i]);
      char *comp = args[i];
      printf("%s\n", comp);
      if (!strcmp(comp, ";")) {
        printf("found semicolon\n");
        args1 = calloc(i - start, sizeof(char *));
        for (j = start; j < i; j++) {
          args1[j - start] = args[j];
        }
        printf("executing from %d to %d\n", start, i); // i is where semicolon is
        execute_args(args1);
        start = i + 1; // sets the start to the new beginning after semi
  
      }
    }

    /*
    // if there was no semi colon after the rest
    args1 = calloc(i, sizeof(char *));
    for (i = start; i < ARG_NUM; i++) {
      args1[i - start] = args[i];
    }
    */
  

    // current problem- if it says exit before last command, it doesn't work
    exit = execute_args(args);
    if (exit == -1) {
      printf("please give a good terminal command\n");
    }

  }
  return 0;
}