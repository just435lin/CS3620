#include <stdio.h>
#include <stdlib.h>
void fib(int);

int main(int argc, char* argv[]) {
    int n = 0;
    if (argc > 0) {
        n = atoi(argv[1]);
        if (n > 0) {
            fib(n);
            return 0;
        }
    }
    printf("Please enter a valid integer greater than 0\n");
    while (n < 1) {
        scanf("%d", &n);
        if (n <= 0) {
            printf("Invalid input, try again\n");
        }
    }
    fib(n);
}

void fib(int n) {
    int n1 = 0;
    int n2 = 1;
    if (n < 1) {
        printf("Invalid input for fibonacci sequence\n");
        return;
    }
    if (n >= 1) {
        printf("0\n");
    }
    if (n >= 2) {
        printf("1\n");
    }
    for (int i=3;i<=n;i++) {
        printf("%d\n", n1+n2);
        int temp = n2;
        n2 = n1+n2;
        n1 = temp;
    }
}