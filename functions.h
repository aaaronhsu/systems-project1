#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

// for now the max args it takes is 5 if you input during the prompt
#define ARG_NUM 10
#define ARG_SIZE 500

char ** parse_args(char *line, int session);
void add_to_history(char *line, int session);
char * read_args();
void print_command_not_found(char ** args);
int semi_exec(char ** args);
int execute_args(char **args);

#endif