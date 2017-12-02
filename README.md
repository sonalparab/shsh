# shsh: a shell by s h

## Project 1: Shell-ing Out Commands with Sonal Parab, Helen Ye

## Features
* Multiple commands in one line.
* Redirection.
* Piping (Single pipe only?)

## Attempted
* Feature

## Bugs:
* If you try to cd into a directory that doesn't exist, it does not inform you that the directory doesn't exist
* Does not work with commands that have tabs

## Files & Function Headers

### `exec.h`
```c
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
```

### `main.h`
```c
/*
 * Prints a prompt that resembles the default bash shell prompt
 */
void print_prompt();
```
