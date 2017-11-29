#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#ifndef EXEC_H
#define EXEC_H

/*
 * Runs a singular command
 */
void run_command(char *, char *);

/*
 * The execution of the shell.
 */
void run(char *);

#endif
