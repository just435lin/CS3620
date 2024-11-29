#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "bank_interface.h"
#include "benchmark.h"

typedef struct account {
    unsigned int account;
    int balance;
    struct account *next;
} account_t;

typedef struct ledger {
    account_t *head;
    account_t *tail;
    pthread_mutex_t lock;
} ledger_t;

int create_account(unsigned int account, void *ledger) {
    // TODO:
    return -1;
}

void list_accounts(void *ledger) {
   // TODO:
}

int modify_balance(unsigned int account, int amount, void *ledger) {
    // TODO:
    return 0;
}

int main() {
    ledger_t ledger;
    ledger.head = NULL;
    ledger.tail = NULL;
    pthread_mutex_init(&ledger.lock, NULL);
    
    double time_taken;
    int accounts = 100;
    printf("accounts: %d\n", accounts);
    time_taken = benchmark_driver(1, 10000, accounts, &ledger);
    printf("%f\n", time_taken);

    time_taken = benchmark_driver(10, 10000, accounts, &ledger);
    printf("%f\n", time_taken);

    time_taken = benchmark_driver(100, 10000, accounts, &ledger);
    printf("%f\n", time_taken);

    time_taken = benchmark_driver(1000, 10000, accounts, &ledger);
    printf("%f\n", time_taken);

    return 0;
}