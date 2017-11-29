# shsh: a shell by s h

## Project 1: Shell-ing Out Commands with Sonal Parab, Helen Ye

## Features
* Multiple commands in one line.
* Redirection.

## Attempted
* Feature

## Bugs:
* After an invalid command is submitted, it takes +1 exit.
    * That is, after submitting 3 invalid commands, you have to run exit 4 times.

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
 * The execution of the shell.
 */
void run(char *);
```

### `main.h`
```c
/*
 * Prints a prompt that resembles the default bash shell prompt
 */
void print_prompt();
```
