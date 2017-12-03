#include "exec.h"
#include "main.h"

sigjmp_buf env;

static void sighandler(int signo) {
    if (signo == SIGINT) {
        if (get_pid() > 0) {
            kill(get_pid(), SIGINT);
        }
        printf("\n");
        siglongjmp(env, SIGJMPENV);
        exit(0);
    }

    if (signo == SIGCHLD) {
        int pid;
        int status;
        pid = waitpid(-1, &status, WNOHANG);
    }
}

int main(){
    signal(SIGINT, sighandler);
    signal(SIGCHLD, sighandler);

    char buffer[256];

    while (1) {
        // Use if you want to do something specific catching ctrl-c
        if (sigsetjmp(env, 1) == SIGJMPENV){
        }

        print_prompt();

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        run(buffer);
    }
}

void print_prompt() {

    // Lengths based off of google searches for the max lengths
    // of username and hostname
    char user[33];

    uid_t u = getuid();
    if (u) {
        struct passwd *p = getpwuid(u);
        if (p) {
            strcpy(user, p->pw_name);
        } else {
            strcpy(user, "user");
        }
    }

    char hostname[65];
    gethostname(hostname, sizeof(hostname));

    char cwd[256];
    char wd[256];
    getcwd(wd, sizeof(wd));

    char *homedir;
    homedir = getenv("HOME");
    if (strstr(wd, homedir) && strcspn(wd, homedir) == 0) {
        strcpy(cwd, "~");
        strcat(cwd, wd + strlen(homedir));
    } else {
        strcpy(cwd, wd);
    }

    printf(GREEN "%s@%s" RESET ":" YELLOW "%s " RESET "$ ", user, hostname, cwd);
}
