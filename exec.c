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
            char *filename;
            if (args[i+1]) {
                filename = args[i+1];
            } else {
                filename = args[i] + 1;
            }
            int fd = open(filename, O_RDONLY);
            dup2(fd, 0);
            close(fd);
            args[i] = 0;
        }
    }
}

int piping(char *args[256]){
    int i;
    int r = 1;
    char *cmd = (char*)calloc(256, sizeof(char));
    for (i = 0; args[i]; i++){
        int j;
        for(j = 0;args[i][j];j++){
            if (args[i][j] == '|'){
                r = 0;
            }
        }
        strcat(cmd,args[i]);
    }
    if(r == 0){
        FILE *p;
        p = popen(cmd,"w");
        char buffer[256];
        fgets(buffer,sizeof(buffer),p);
        buffer[sizeof(buffer) - 1] = 0;
        pclose(p);
    }
    return r;
}

void run_command(char *cmd, char buffer[]) {
    char *arg;
    char *args[256];
    int ran = 1;

    if (strlen(cmd) == 0) {
        return;
    }

    int i;
    for (i = 0; cmd; i++) {
        arg = strsep(&cmd, " ");
        //to handle whitespace in front
        // check if arg is an empty string
        // and that cmd is not null
        // until reaching an actual argument if there is one
        while(strcmp(arg,"") == 0 && cmd){
            arg = strsep(&cmd, " ");
        }
        //to handle whitespace at the end of a command
        // if the arg at the end of a command is an empty string, break
        if(strcmp(arg,"") == 0)
            break;
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
        // Set ran to 0 because command was run
        ran = 0;
        int chdir_ret;
        if (args[1]) {
            chdir_ret = chdir(args[1]);
        } else {
            chdir_ret = chdir(getenv("HOME"));
        }
        if (chdir_ret == -1) {
            printf("%s\n", strerror(errno));
        }
        return;
    }

    // If ran is 1, check for piping
    // Returns 0 if the command was run
    // Returns 1 if command did not need piping
    if (ran)
        ran = piping(args);

    //Run through child process if ran is 1
    // meaning the command was not run yet
    if (ran){
        int f = fork();
        if (f == 0) {
            redirect_stdout(args);
            redirect_stdin(args);
            execvp(args[0], args);


            printf("Invalid command: %s\n", args[0]);
            exit(1);
        }
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
