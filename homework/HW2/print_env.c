#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]) {
    int length = sizeof(envp)/sizeof(envp[0]);
    printf("%d",length);
    length = 7;
    for (int i=0;i<length;i++) {
        printf("%s\n", envp[i]);
    }
    char* env = getenv("USER"); 
    printf("%s\n", env);

    char* TP = getenv("TERM_PROGRAM");
    char* shell = getenv("SHELL");
    char* term = getenv("TERM");
    char* tmpdir = getenv("TMPDIR");
    char* tpv = getenv("TERM_PROGRAM_VERSION");
    char* ts_ID = getenv("TERM_SESSION_ID");
    char* user = getenv("USER");
    printf("TERM_PROGRAM=%s\n", TP);
    printf("SHELL=%s\n", shell);
    printf("TERM=%s\n", term);
    printf("TMPDIR=%s\n", tmpdir);
    printf("TERM_PROGRAM_VERSION=%s\n", tpv);
    printf("TERM_SESSION_ID=%s\n", ts_ID);
    printf("USER=%s\n", user);
}