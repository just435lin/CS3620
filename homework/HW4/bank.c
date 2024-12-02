#include <stdio.h>
#include <stdlib.h>
#include "bank_interface.h"
#include <stdbool.h>

typedef struct account {
    unsigned int account;
    int balance;
    struct account *next;
} account_t;

typedef struct ledger {
    account_t *head;
    account_t *tail;
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
        return -1;
    }
    return 0;
}

void list_accounts(void *ledger) {
    ledger_t *bank = ledger;
    if (bank->head == NULL) { //zero accounts exists
        printf("No accounts have been created\n");
        return; 
    } 
    if (bank->head == bank->tail) { //only one account exist
        unsigned int acc_num = bank->head->account;
        int acc_bal = bank->head->balance;
        printf("%u: $%d\n", acc_num, acc_bal);
        return;
    }

    account_t *curr = bank->head;
    while (curr != NULL) {
        unsigned int acc_num = curr->account;
        int acc_bal = curr->balance;
        printf("%u: $%d\n", acc_num, acc_bal);
        curr = curr->next;
    }
}

int modify_balance(unsigned int account, int balance, void *ledger) {
    account_t* acc = contains_account(account, ledger);
    if (acc != NULL) {
        acc->balance = acc->balance + balance;
        return 0;
    }
    return -1;
}

int main() {
    ledger_t ledger;
    ledger.head = NULL;
    ledger.tail = NULL;

    create_account(0, &ledger);
    create_account(1, &ledger);
    create_account(2, &ledger);

    list_accounts(&ledger);
    
    modify_balance(1, 10, &ledger);
    modify_balance(0, -100, &ledger);
    modify_balance(123, -100, &ledger);

    list_accounts(&ledger);

    return 0;
}