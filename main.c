#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    char buffer[256];
    char *cmd = buffer;
    char *arg;
    char *args[256];

    char user[128];
    getlogin_r(user, sizeof(user));

    char hostname[128];
    gethostname(hostname, sizeof(hostname));

    char cwd[256];
    getcwd(cwd, sizeof(cwd));

    char prompt[512];
    sprintf(prompt, "%s@%s:%s $ ", user, hostname, cwd);

    printf("%s", prompt);
    while (fgets(buffer, sizeof(buffer), stdin)) {

        cmd = buffer;
        buffer[strlen(buffer) - 1] = 0;

        int i;
        for (i = 0; cmd; i++) {
            arg = strsep(&cmd, " ");
            args[i] = arg;
        }

        args[i] = 0;

        // If exiting from shell
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // If changing directory
        if (strcmp(args[0], "cd") == 0) {
            chdir(args[1]);

            sprintf(prompt, "%s@%s:%s $ ", user, hostname, cwd);
            printf("%s", prompt);
            continue;
        }

        // Run through child process otherwise
        int f = fork();
        if (f == 0) {
            execvp(args[0], args);
        }

        int status;
        wait(&status);

        sprintf(prompt, "%s@%s:%s $ ", user, hostname, cwd);
        printf("%s", prompt);
    }
}
