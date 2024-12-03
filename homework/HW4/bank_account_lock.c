#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "benchmark.h"

typedef struct account {
    unsigned int account;
    int balance;
    struct account *next;
    pthread_mutex_t lock;
} account_t;

typedef struct ledger {
    account_t *head;
    account_t *tail;
    pthread_rwlock_t lock;
} ledger_t;

account_t* get_account(unsigned int account, void *ledger) {
    ledger_t *bank = ledger;
    if (bank->head == NULL) { //zero accounts exists
        return NULL;
    } 

    if (bank->head == bank->tail) { //only one account exist
        if (bank->head->account == account) {
            return bank->head;
        } else {
            return NULL;
        }
    }

    account_t *curr = bank->head;
    while (curr != NULL) {
        if (curr->account == account) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int create_account(unsigned int account, ledger_t *ledger) {
    pthread_rwlock_t *lock = &(((ledger_t*)ledger)->lock);
    pthread_rwlock_wrlock(lock);
    int status = 0;
    ledger_t *bank = ledger;
    account_t *new_account = (account_t*)malloc(sizeof(account_t));
    new_account->account = account;
    new_account->balance = 0;
    new_account->next = NULL;
    pthread_mutex_init(&(new_account->lock), NULL);

    if (bank->head == NULL) {
        bank->head = new_account;
        bank->tail = new_account;
    } else if (get_account(account, ledger) == NULL) {
            bank->tail->next = new_account;
            bank->tail = new_account;
    } else {
        status = -1;
    }
    pthread_rwlock_unlock(lock);
    return status;
}

void list_accounts(void *ledger) {
    pthread_rwlock_t *lock = &(((ledger_t*)ledger)->lock);
    pthread_rwlock_wrlock(lock);
    ledger_t *bank = ledger;
    if (bank->head == NULL) {                       //zero accounts exists
        printf("No accounts have been created\n");
    } else if (bank->head == bank->tail) {          //only one account exist
        unsigned int acc_num = bank->head->account;
        int acc_bal = bank->head->balance;
        printf("%u: $%d\n", acc_num, acc_bal);
    } else {
        account_t *curr = bank->head;
        while (curr != NULL) {
            unsigned int acc_num = curr->account;
            int acc_bal = curr->balance;
            printf("%u: $%d\n", acc_num, acc_bal);
            curr = curr->next;
        }
    }
    pthread_rwlock_unlock(lock);
}

int modify_balance(unsigned int account, int amount, ledger_t *ledger) {
    pthread_rwlock_t *lock = &(((ledger_t*)ledger)->lock);
    pthread_rwlock_wrlock(lock);
    int status = -1;
    account_t* acc = get_account(account, ledger);
    pthread_mutex_t *acc_lock = &(acc->lock);
    if (acc != NULL) {
        pthread_mutex_lock(acc_lock);
        acc->balance = acc->balance + amount;
        pthread_mutex_unlock(acc_lock);
        status = 0;
    }
    pthread_rwlock_unlock(lock);
    return status;
}



int main() {
    ledger_t ledger;
    ledger.head = NULL;
    ledger.tail = NULL;
    pthread_rwlock_init(&ledger.lock, NULL);


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