#include "exec.h"
#include "main.h"

int main(){
    char buffer[256];
    print_prompt();

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        run(buffer);
        print_prompt();

    }
}

void print_prompt() {

    // Lengths based off of google searches for the max lengths
    // of username and hostname
    char user[33];
    // Doesn't work outside of tmux and idk why
    /* getlogin_r(user, sizeof(user)); */

    uid_t u = getuid();
    if (u) {
        struct passwd *p = getpwuid(u);  // Check for NULL!
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
