#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>

#define BLUE "\001\033[34m\002"
#define GREEN "\001\033[32m\002"
#define MAGENTA "\001\033[35m\002"
#define RED "\001\033[31m\002"
#define RESET "\001\033[0m\002"
#define YELLOW "\001\033[33m\002"

/*
 * Prints a prompt that resembles the default bash shell prompt
 */
void print_prompt();
