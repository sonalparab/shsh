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

    printf(">>> ");
    while(fgets(buffer, sizeof(buffer), stdin)) {
        cmd = buffer;
        buffer[strlen(buffer) - 1] = 0;

        int i;
        for (i = 0; cmd; i++) {
            arg = strsep(&cmd, " ");
            args[i] = arg;
        }

        args[i] = 0;

        int f = fork();
        if (f == 0) {
            execvp(args[0], args);
        }

        int status;
        wait(&status);

        printf(">>> ");
    }
}
