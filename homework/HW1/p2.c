#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void primes(int);

int main(int argc, char* argv[]) {
    int n = 0;
    if (argc > 0) {
        n = atoi(argv[1]);
        if (n > 0) {
            primes(n);
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
    primes(n);
} 

void primes(int n) {
    if (n < 1) {
        printf("Invalid input for primes\n");
        return;
    }
    if (n >= 1) {
        printf("1\n");
    }
    if (n >= 2) {
        printf("2\n");
        if (n == 2) {
            return;
        }
    }
    int p[n];
    for (int i=0;i<n;i++) {
        p[i] = 0;
    }
    p[0] = 1;
    p[1] = 2;
    int curr = 3;
    for (int i=2;i<n;i++) {
        
        while (p[i] == 0) {
            bool comp = false;
            int k = 1;
            while (k<i && !comp) {
                if (curr % p[k] == 0) {
                    comp = true;
                }
                k++;
            }
            if (!comp) {
                p[i] = curr;
                printf("%d\n", curr);
            }
            curr++;
            if (curr > n) {
                return;
            }
        }
        
    }
}