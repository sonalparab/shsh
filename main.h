#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>

// These colors make things weird outside of tmux
// So many weird things outside of tmux
/* #define BLUE "\001\033[34m\002" */
/* #define GREEN "\001\033[32m\002" */
/* #define MAGENTA "\001\033[35m\002" */
/* #define RED "\001\033[31m\002" */
/* #define RESET "\001\033[0m\002" */
/* #define YELLOW "\001\033[33m\002" */
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/*
 * Prints a prompt that resembles the default bash shell prompt
 */
void print_prompt();
