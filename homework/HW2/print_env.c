#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* environ[]) {
    int index = 0;
    while (environ[index]) {
        printf("%s\n",environ[index]);
        index++;
    }
}