#include "exec.h"
#include "main.h"

int main(){
    char buffer[256];
    char * prompt;
    printf("%s", prompt = get_prompt());

    while (fgets(buffer, sizeof(buffer), stdin)) {

        run(buffer);

        printf("%s", prompt = get_prompt());
    }
    free(prompt);
}

char * get_prompt() {
    char *prompt = (char *)calloc(512,sizeof(char));

    // Lengths based off of google searches for the max lengths
    // of username and hostname
    char user[33];
    getlogin_r(user, sizeof(user));

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

    sprintf(prompt, "%s@%s:%s $ ", user, hostname, cwd);
    return prompt;
}
