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

char ** parse_args(char *line);
char ** parse_command(char *line);
int count_semi(char *line);
char * read_args();

int execute_args(char **args);

#endif