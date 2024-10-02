#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[], char* environ[]) {
    char* lastLine = "TERM_PROGRAM=vscode";
    int index = 0;
    while (environ[index]) {
        
        printf("%s\n",environ[index]);
        if (strcmp(environ[index],lastLine)==0) {
            return 0;
        }
        index++;

    }
}