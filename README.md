# shsh: a shell by s h

## Project 1: Shell-ing Out Commands with Sonal Parab, Helen Ye

## Features
* Multiple commands in one line separated by `;`
* Redirection
* Piping (Single pipe only)
* Extra whitespace in commands
* `Ctrl-c` sends to children & doesn't affect main parent

## Attempted
* Feature

## Bugs:
* Does not work with commands that have tabs
* When redirecting, there needs to be a space before and after the redirection symbol
* While the homedir is substituted with `~` in the prompt, trying to use it as a path will fail
* Can not echo anything with a semicolon or bar, even if its in quotes
* There are hard limits on the lengths of the input, working directory in prompt (255 + `NULL`)

## Files & Function Headers

### `exec.h`
```c
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
void run_command(char *, char *);

/*
 * Inputs: char * buffer - the buffer returned from the shell, including ;'s
 * Returns: None
 *
 * The execution of the shell
 */
void run(char *);
```

### `main.h`
```c
/*
 * Inputs:
 * * * int signo -- the signal received
 * Returns: None
 *
 * Signal handling for SIGINT
 * Thanks to
 * https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/
 */
static void sighandler(int signo);

/*
 * Inputs: None
 * Returns: None
 *
 * Prints a prompt that resembles the default bash shell prompt
 */
void print_prompt();
```
