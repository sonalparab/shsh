#include "exec.h"

void run_command(char *cmd, char buffer[]) {
    char *arg;
    char *args[256];

    int i;
    for (i = 0; cmd; i++) {
        arg = strsep(&cmd, " ");
        args[i] = arg;
    }

    args[i] = 0;

    // If exiting from shell
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    // If changing directory
    // currently breaks things sometimes
    if (strcmp(args[0], "cd") == 0) {
        if (args[1]) {
            chdir(args[1]);
        } else {
            chdir(getenv("HOME"));
        }

        //printf("%s", prompt = get_prompt());
        //continue;
    }

    // Run through child process otherwise
    int f = fork();
    if (f == 0) {
        execvp(args[0], args);
    }
    int status;
    wait(&status);
    return;
}

void run(char buffer[]){
    char *cmd = buffer;
    char *restCmd = buffer;

    cmd = buffer;
    restCmd = buffer;
    buffer[strlen(buffer) - 1] = 0;
    cmd = strsep(&restCmd, ";");

    while(cmd){
        run_command(cmd,buffer);
        cmd = strsep(&restCmd, ";");
    }
}
