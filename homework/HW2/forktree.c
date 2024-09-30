#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdlib.h>

int getStatus(int status) {
    int exitstatus = -1;
    if (WIFEXITED(status)) {
        exitstatus = WEXITSTATUS(status);
    }
    return exitstatus;
}

int main() {
    int p = 0;
    int status = 0;
    int sum = 0;

    pid_t PL1 = fork();
    if (PL1==0) {p=1;}
    if (PL1!=0) {
        PL1 = fork();
        if (PL1==0) {p=2;}
    }
    
    if (PL1!=0) {
        wait(&status);
        sum = sum+getStatus(status);
        wait(&status);
        sum = sum+getStatus(status);
    } else {
        pid_t PL2 = fork();
        if (PL2==0) {
            if (p==1) {
                p=3;
            } else {
                p=5;
            }
        }
        if (PL2!=0) {
            PL2 = fork();
            if (PL2==0) {
                if (p==1) {
                    p=4;
                } else {
                    p=6;
                }
            }
        }

        if (PL2!=0) {
            wait(&status);
            sum = sum+getStatus(status);
            wait(&status);
            sum = sum+getStatus(status);
            printf("%d",p);
            exit(sum);
        } else {
            printf("%d",p);
            exit(1);
        }
    }
    printf("%d",p);
    printf("\n%d\n",sum);

}