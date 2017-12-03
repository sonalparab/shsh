#include "exec.h"

int pid = -1;

int get_pid() {
    return pid;
}

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
    // Default is that command is not run, r = -1
    int r = -1;
    char *cmd = (char*)calloc(256, sizeof(char));
    
    for (i = 0; args[i]; i++){
        int j;
        for(j = 0;args[i][j];j++){
	    // Check for piping in command
	    // If true, the command will be run with
	    // popen, set r to 0
            if (args[i][j] == '|'){
                r = 0;
            }
        }
        strcat(cmd,args[i]);
    }

    // Run command with popen if needed
    if(!r){
        FILE *p;
        p = popen(cmd,"w");
        char buffer[256];
        fgets(buffer,sizeof(buffer),p);
        buffer[sizeof(buffer) - 1] = 0;
        pclose(p);
    }
    
    // Return whether the command was run or not
    return r;
}

void run_command(char *cmd, char buffer[]) {
    char *arg;
    char *args[256];
    int ran;

    // If command is empty
    if (strlen(cmd) == 0) {
        return;
    }

    // Building the command
    int i;
    for (i = 0; cmd; i++) {
        arg = strsep(&cmd, " ");
        // To handle whitespace in front
        // Check if arg is an empty string
        // and that cmd is not null
        // until reaching an actual argument if there is one
        while(strcmp(arg,"") == 0 && cmd){
            arg = strsep(&cmd, " ");
        }
        // To handle whitespace at the end of a command
        // If the arg at the end of a command is an empty string, break
        if(strcmp(arg,"") == 0 || strcmp(arg," ") == 0)
            break;
	args[i] = arg;
    }

    // If command was only whitespace, i is 0
    if(i == 0)
      return;
    
    args[i] = 0;

    // Running the command
    
    // If exiting from shell
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    // If changing directory
    if (strcmp(args[0], "cd") == 0) {
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

    // Check for piping
    // Returns 0 if the command was run with popen
    // Returns -1 if command did not need piping
    ran = piping(args);

    // Run through child process if ran is -1
    // meaning the command was not run yet
    if (ran){
        pid = fork();
        if (pid == 0) {
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
