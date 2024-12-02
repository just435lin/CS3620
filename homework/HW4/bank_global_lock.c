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

account_t* contains_account(unsigned int account, void *ledger) {
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

int create_account(unsigned int account, void *ledger) {
    pthread_mutex_t *lock = &(((ledger_t*)ledger)->lock);
    pthread_mutex_lock(lock);
    int status = 0;
    ledger_t *bank = ledger;
    account_t *new_account = (account_t*)malloc(sizeof(account_t));
    new_account->account = account;
    new_account->balance = 0;
    new_account->next = NULL;

    if (bank->head == NULL) {
        bank->head = new_account;
        bank->tail = new_account;
    } else if (contains_account(account, ledger) == NULL) {
            bank->tail->next = new_account;
            bank->tail = new_account;
    } else {
        status = -1;
    }
    pthread_mutex_unlock(lock);
    return status;
}

void list_accounts(void *ledger) {
    pthread_mutex_t *lock = &(((ledger_t*)ledger)->lock);
    pthread_mutex_lock(lock);
    ledger_t *bank = ledger;
    if (bank->head == NULL) { //zero accounts exists
        printf("No accounts have been created\n");
        pthread_mutex_unlock(lock);
        return; 
    } 
    if (bank->head == bank->tail) { //only one account exist
        unsigned int acc_num = bank->head->account;
        int acc_bal = bank->head->balance;
        printf("%u: $%d\n", acc_num, acc_bal);
        pthread_mutex_unlock(lock);
        return;
    }

    account_t *curr = bank->head;
    while (curr != NULL) {
        unsigned int acc_num = curr->account;
        int acc_bal = curr->balance;
        printf("%u: $%d\n", acc_num, acc_bal);
        curr = curr->next;
    }
    pthread_mutex_unlock(lock);
}

int modify_balance(unsigned int account, int amount, void *ledger) {
    pthread_mutex_t *lock = &(((ledger_t*)ledger)->lock);
    pthread_mutex_lock(lock);
    int status = -1;
    account_t* acc = contains_account(account, ledger);
    if (acc != NULL) {
        acc->balance = acc->balance + amount;
        status = 0;
    }
    pthread_mutex_unlock(lock);
    return status;
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