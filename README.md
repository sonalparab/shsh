# shsh: a shell by s h

## Project 1: Shell-ing Out Commands with Sonal Parab, Helen Ye

## Features
* Multiple commands in one line separated by `;`
* Redirection
* Piping (Single pipe only)
* Extra whitespace in between commands
* `Ctrl-c` sends to children & doesn't affect main parent

## Attempted
* Feature

## Bugs:
* Does not work with commands that have tabs
* When redirecting, there needs to be a space before and after the redirection symbol
* While the homedir is substituted with `~` in the prompt, trying to use it as a path will fail

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
