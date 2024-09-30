#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int status = 0;
    int sum = 0;
    pid_t PL1 = fork();
    if (PL1!=0) { //parent process
        pid_t PL2 = fork();
        if (PL2!=0) {
            waitpid(PL2,&status,0);
            if (WIFEXITED(status)) {
                int exitstatus = WEXITSTATUS(status);
                sum = sum+exitstatus;
            }
        } else {
            exit(1);
        }

        waitpid(PL1, &status, 0);
        if (WIFEXITED(status)) {
            int exitstatus = WEXITSTATUS(status);
            sum = sum+exitstatus+1;
            printf("%d\n",sum);
        }
        
    } else { //child process
        pid_t PL3 = fork();
        if (PL3!=0) { //parent process
            waitpid(PL3, &status, 0);
            if (WIFEXITED(status)) {
                int exitstatus = WEXITSTATUS(status);
                exit(exitstatus+1);
            }
        } else {
            exit(1);
        }
    }


}