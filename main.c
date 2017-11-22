#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    char buffer[16];
    char *cmd = buffer;
    char *args[16] = {};

    printf(">>> ");
    while(fgets(buffer, sizeof(buffer), stdin)) {
        cmd[sizeof(cmd)-1] = 0;
        int i;
        // SEGFAULTS
        for (i = 0; cmd; i++) {
            args[i] = strsep(&cmd, " ");
            printf("args %d: %s\n", i, args[i]);
        }
        printf(">>> ");
    }
}
