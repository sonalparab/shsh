#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#ifndef EXEC_H
#define EXEC_H

/*
 * Returns the value of the pid var used in this shell
 */
int get_pid();

/*
 * Handling redirecting output
 */
void redirect_stdout(char **args);

/*
 * Handling redirecting input
 */
void redirect_stdin(char **args);

/*
 * Runs a singular command
 */
void run_command(char *, char *);

/*
 * The execution of the shell
 */
void run(char *);

/*
 * Handles commands with pipes
 */
int piping(char *args[256]);

#endif
