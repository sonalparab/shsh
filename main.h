#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include <setjmp.h>

// Used for ctrl-c functionality
// 8 because why not
#define SIGJMPENV 8

// Colors used in the shell
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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
