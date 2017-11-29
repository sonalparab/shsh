#include "exec.h"

void redirect_stdout(char *args[256]) {
    int i;
    for (i = 0; args[i]; i++) {

        /*
        char* red = strchr(args[i], '>');
        if (!red) {
            continue;
        }
        */

        int fd;
        char* filename = args[i+1];
        int append = 0;

        if (strlen(args[i]) >= 2 && args[i][1] == '>') {
            printf("redirecting...");
            if (args[i][2] == '>') {
                append = O_APPEND;
            }

            // Redirect stderr
            if (args[i][0] == '2') {
                fd = open(filename, O_WRONLY | append | O_CREAT, 0664);
                dup2(fd, 2);
                close(fd);
            } else if (args[i][0] == '&') {
                // Redirect stdout and stderr
                fd = open(filename, O_WRONLY | append | O_CREAT, 0664);
                dup2(fd, 1);
                dup2(fd, 2);
                close(fd);
            } else {
                // Redirect stdout and append
                fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
                dup2(fd, 1);
                close(fd);
            }
            args[i] = 0;
        } else if (args[i][0] == '>') {
            fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
            dup2(fd, 1);
            close(fd);
            args[i] = 0;
        }
    }
}

void redirect_stdin(char *args[256]) {
    int i;
    for (i = 0; args[i]; i++) {
        if (args[i][0] == '<') {
            char * filename = args[i+1];
            int fd = open(filename, O_RDONLY);
            dup2(fd, 0);
            close(fd);
            args[i] = 0;
        }
    }
}

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
        redirect_stdout(args);
        redirect_stdin(args);
        execvp(args[0], args);
        printf("Invalid command\n");
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
