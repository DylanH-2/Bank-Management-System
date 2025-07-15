#ifndef BANKINGHEAD_H
#define BANKINGHEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct // struct for transactions
{
    char type[50];
    double amount;
} Transaction;

typedef struct // main struct
{
    char name[50];
    double balance;
    int accountNum;
    int pin;
    int totalTransactions;
    Transaction transactions[50]; // 50 total transactions
} Account;

typedef struct node // memory allocation
{
    Account data;
    struct node *next;

} NODE;

extern NODE *head;

void createAccount(void);
void showAccounts(NODE *ptr);
void editAccount(NODE *ptr);
void withdrawOrDeposit(NODE *ptr);
void deleteAccount(NODE *ptr);
void freeAll(NODE *ptr);
void showTransactions(NODE *ptr);
void showRecursive(NODE *ptr);

#endif
