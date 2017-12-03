# shsh: a shell by s h

## Project 1: Shell-ing Out Commands with Sonal Parab, Helen Ye

## Features
* Multiple commands in one line separated by `;`
* Redirection
* Piping (Single pipe only)
* Extra whitespace at the beginning, end, or in between commands
* `Ctrl-c` sends to children & doesn't affect main parent

## Attempted
* Feature

## Bugs:
* Does not work with commands that have tabs
* When redirecting, there needs to be a space before and after the redirection symbol
* While the homedir is substituted with `~` in the prompt, trying to use it as a path will fail
* Command of only whitespace will not work (but works if only one space)
* Can not echo anything with a semicolon or bar, even if its in quotes

## Files & Function Headers

### `exec.h`
```c
/*
 * Returns the value of the pid used by this shell
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
```

### `main.h`
```c
/*
 * Signal handling for SIGINT
 * Thanks to
 * https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/
 */
static void sighandler(int signo);

/*
 * Prints a prompt that resembles the default bash shell prompt
 */
void print_prompt();
```
