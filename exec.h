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
 * Inputs: None
 * Returns: The value of the pid variable (NOT THE ACTUAL PID)
 *
 * shsh uses its own pid variable
 */
int get_pid();

/*
 * Inputs:
 * * * char ** args -- representing a parsed command
 * Returns: None
 *
 * Handles redirecting output
 */
void redirect_out(char ** args);

/*
 * Inputs:
 * * * char ** args -- representing a parsed command
 * Returns: None
 *
 * Handles redirecting input
 */
void redirect_in(char **);

/*
 * Inputs:
 * * * char ** args -- representing a parsed command
 * Returns: Int representing if the command was run by this fxn
 *
 * Handles commands with pipes
 */
int piping(char **);

/*
 * Inputs:
 * * * char *cmd -- a singular command (no ; separating) that has not yet been parsed
 * Returns: None
 *
 * Runs a singular command
 */
void run_command(char *);

/*
 * Inputs: char * buffer - the buffer returned from the shell, including ;'s
 * Returns: None
 *
 * The execution of the shell
 */
void run(char *);

#endif
