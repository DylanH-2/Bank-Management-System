#include "bankinghead.h"
#include <ctype.h>

void createAccount(void) // option1
{
    char nameInput[50];
    char balanceInput[50];
    char enteredPin[5];
    int validChar = 0;
    int validDigit = 0;
    int validPin = 0;

    printf("Enter the details needed to create an account \n");

    while (!validChar) // make sure user only enters letters
    {
        printf("Account name (letters only): \n");
        scanf("%50s", nameInput);
        validChar = 1;
        for (int i = 0; nameInput[i] != '\0'; i++)
        {
            if (!isalpha((unsigned char)nameInput[i])) // unsiged char cast helps ensure nameInput is treated as a valid character from 0-255
            {
                validChar = 0;
                printf("Invalid name. Only letters are allowed.\n");
                break;
            }
        }
    }

    NODE *newAccount = (NODE *)malloc(sizeof(NODE)); // allocate memory for a new node
    if (newAccount == NULL)
    {
        printf("\nMEMORY ALLOCATION FAILED\n");
        return;
    }

    strcpy(newAccount->data.name, nameInput);
    newAccount->data.totalTransactions = 0;

    while (!validDigit) // make sure user only enters numbers
    {
        printf("Type in initial balance: ");
        scanf("%50s", balanceInput); // have to take in the balance as a string

        validDigit = 1;
        int dotCount = 0;
        for (int i = 0; balanceInput[i] != '\0'; i++)
        {
            if (balanceInput[i] == '.')
            {
                dotCount++;
                if (dotCount > 1) // ensure only one decimal
                {
                    validDigit = 0;
                    break;
                }
            }
            else if (!isdigit((unsigned char)balanceInput[i]))
            {
                validDigit = 0;
                break;
            }
        }
        if (!validDigit)
        {
            printf("Invalid balance. Only numbers are allowed.\n");
        }
    }
    newAccount->data.balance = atof(balanceInput); // ASCII to float
    int i = newAccount->data.totalTransactions;
    newAccount->data.transactions[i].amount = newAccount->data.balance;
    strcpy(newAccount->data.transactions[i].type, "Initial deposit");
    newAccount->data.totalTransactions++;

    while (!validPin) // check if the pin is correct restrictions
    {
        printf("Enter 4 digit pin: \n");
        scanf("%s", enteredPin);
        validPin = 1;
        int pinLen = strlen(enteredPin);
        if (pinLen != 4)
        {
            printf("\nPin is too long or short \n");
            validPin = 0;
            continue; // skip next iternation
        }
        for (int i = 0; enteredPin[i] != '\0'; i++)
        {
            if (!isdigit((unsigned char)enteredPin[i]))
            {
                printf("No symbols and only 4 digits allowed \n");
                validPin = 0;
                break;
            }
        }

        if (!validPin)
        {
            printf("No symbols and only 4 digits allowed \n");
        }
    }

    newAccount->data.pin = atoi(enteredPin);
    newAccount->data.accountNum = rand() % 9000 + 1000;
    newAccount->next = NULL;

    if (head == NULL)
    {
        head = newAccount;
    }
    else
    {
        NODE *ptr = head;
        while (ptr->next != NULL) // insert new node at end
        {
            ptr = ptr->next;
        }
        ptr->next = newAccount;
    }

    printf("Account created\n");
    printf("Account number: %d Name: %s Balance: $%.2f Transactions: %d\n", newAccount->data.accountNum, newAccount->data.name, newAccount->data.balance, newAccount->data.totalTransactions);
}

void showAccounts(NODE *ptr) // option2
{
    if (head == NULL)
    {
        printf("\nNo accounts to show. \n");
        return;
    }
    else
    {
        while (ptr != NULL)
        {
            printf("Account number: %d Name: %s Balance: $%.2f Transactions: %d\n", ptr->data.accountNum, ptr->data.name, ptr->data.balance, ptr->data.totalTransactions);
            ptr = ptr->next;
        }
    }
}

void editAccount(NODE *ptr) // option3
{
    char nameInput[50];
    int found = 0;
    int option;
    char pinInput[4];

    if (ptr == NULL)
    {
        printf("No accounts to edit\n");
        return;
    }

    printf("Enter account name to edit:\n");
    scanf("%50s", nameInput);

    while (ptr != NULL)
    {
        if (strcmp(ptr->data.name, nameInput) == 0) // check if found in list
        {
            found = 1;
            printf("Enter option to edit on account: \n");
            printf("Option 1: Change name, Option 2: Change PIN, Option 3: Reset Balance, Option 0: Cancel \n");
            scanf("%d", &option);
            if (option == 1)
            {
                int valid = 0; // Name found, now ask for new name with validation
                while (!valid) // loop to check name with only letters
                {
                    printf("Type in name to change: \n");
                    scanf("%50s", ptr->data.name); // type in name to change
                    valid = 1;
                    for (int j = 0; ptr->data.name[j] != '\0'; j++)
                    {
                        if (!isalpha((unsigned char)ptr->data.name[j])) // check for no symbols and numbers
                        {
                            valid = 0;
                            printf("Invalid name. Only letters are allowed.\n");
                            break;
                        }
                    }
                }
            }
            else if (option == 2)
            {
                int validPin = 0;
                while (!validPin) // check if the pin is correct restrictions
                {
                    printf("Enter new pin option: \n");
                    scanf("%4s", pinInput);
                    validPin = 1;
                    int pinLen = strlen(pinInput);
                    if (pinLen != 4)
                    {
                        printf("\nPin is too long or short \n");
                        validPin = 0;
                        continue; // skip next iternation
                    }
                    for (int i = 0; pinInput[i] != '\0'; i++)
                    {
                        if (!isdigit((unsigned char)pinInput[i]))
                        {
                            printf("No symbols and only 4 digits allowed \n");
                            validPin = 0;
                            break;
                        }
                    }
                }
                ptr->data.pin = atoi(pinInput); // ASCII to int
            }
            else if (option == 3)
            {
                printf("Resetting balance to $0.00 \n");
                ptr->data.balance = 0;
                break;
            }
            else if (option == 0)
            {
                printf("\nExiting \n");
                break;
            }
            else
            {
                printf("\nNot an option \n");
                break;
            }
            printf("\nAccount updated.\n");
            // found = 1
            break;
        }
        ptr = ptr->next;
    }
    if (!found)
    {
        printf("Name typed in wrong or not found.\n");
    }
}

void withdrawOrDeposit(NODE *ptr) // option4
{
    char nameInput[50];
    char withdrawInput[50];
    char depositInput[50];
    int enteredPin;
    double withdrawAmount = 0.0;
    double depositAmount = 0.0;
    int found = 0;
    int option;

    if (ptr == NULL)
    {
        printf("\nNo account to withdraw or deposit from\n");
        return;
    }

    printf("Enter account name to withdraw or deposit from: \n");
    scanf("%50s", nameInput);

    while (ptr != NULL)
    {
        if (strcmp(ptr->data.name, nameInput) == 0) // check if name input matches
        {
            printf("Enter pin number: \n");
            scanf("%4d", &enteredPin);
            if (ptr->data.pin == enteredPin) // ask for pin number of account
            {
                found = 1;
                printf("Current balance: $%.2lf \n", ptr->data.balance);
                printf("Pick one option: 1. Withdraw   2. Deposit\n");
                scanf("%1d", &option);
                int valid = 0;
                if (option == 1) // withdraw part
                {
                    valid = 0;
                    while (!valid)
                    {
                        printf("Enter withdrawal amount: \n");
                        scanf("%50s", withdrawInput);
                        valid = 1;
                        int dotCount = 0;
                        for (int k = 0; withdrawInput[k] != '\0'; k++)
                        {
                            if (withdrawInput[k] == '.')
                            {
                                dotCount++;
                                if (dotCount > 1)
                                {
                                    printf("Too many decimals \n");
                                    valid = 0;
                                    break;
                                }
                            }
                            else if (!isdigit((unsigned char)withdrawInput[k]))
                            {
                                valid = 0;
                                break;
                            }
                        }
                        if (!valid)
                        {
                            printf("Only enter numbers \n");
                        }
                    }
                    withdrawAmount = atof(withdrawInput);
                    if (withdrawAmount <= 0)
                    {
                        printf("Must be greater than 0 \n");
                        return;
                    }

                    if (withdrawAmount > ptr->data.balance)
                    {
                        printf("Can't be greater than your total");
                        return;
                    }
                    ptr->data.balance -= withdrawAmount;
                    int i = ptr->data.totalTransactions;
                    ptr->data.transactions[i].amount = withdrawAmount;
                    strcpy(ptr->data.transactions[i].type, "withdrawal");
                    ptr->data.totalTransactions++;

                    printf("Succesful withdrawal. New balance: $%.2lf\n", ptr->data.balance);
                    return;
                }
                else if (option == 2) // deposit part
                {
                    valid = 0;
                    while (!valid) // loop to check deposit amount is a number value
                    {
                        printf("Enter deposit amount: \n");
                        scanf("%50s", depositInput);
                        valid = 1;
                        int dotCount = 0;
                        for (int j = 0; depositInput[j] != '\0'; j++)
                        {
                            if (depositInput[j] == '.')
                            {
                                dotCount++;
                                if (dotCount > 1) // check if more than one decimal
                                {
                                    valid = 0;
                                    break;
                                }
                            }
                            else if (!isdigit((unsigned char)depositInput[j])) // take in the number as a string and check each character
                            {
                                valid = 0;
                                break;
                            }
                        }
                        if (!valid)
                        {
                            printf("Invalid amount. Only numbers are allowed.\n");
                        }
                    }
                    depositAmount = atof(depositInput);
                    if (depositAmount <= 0)
                    {
                        printf("Deposit must be greater than zero.\n");
                        return;
                    }
                    ptr->data.balance += depositAmount;
                    int i = ptr->data.totalTransactions;
                    ptr->data.transactions[i].amount = depositAmount;
                    strcpy(ptr->data.transactions[i].type, "deposit");
                    ptr->data.totalTransactions++;
                    printf("Deposit successful. New balance: $%.2lf\n", ptr->data.balance);
                    return;
                }
                else
                {
                    printf("\nNot an option\n");
                    return;
                }
            }
            else
            {
                printf("Incorrect pin \n");
                return;
            }
        }
        ptr = ptr->next;
    }
    if (!found)
    {
        printf("Name not found or typed wrong \n");
    }
}

void deleteAccount(NODE *ptr) // option5
{
    char nameInput[50];
    NODE *prev = NULL;
    if (ptr == NULL)
    {
        printf("No accounts in the system \n");
        return;
    }

    printf("Enter account name to delete: \n");
    scanf("%50s", nameInput);

    while (ptr != NULL)
    {
        if (strcmp(ptr->data.name, nameInput) == 0)
        {
            if (prev == NULL)
            {
                head = ptr->next; // if first one is deleted
            }
            else
            {
                prev->next = ptr->next; // middle or last node
            }
            free(ptr);
            printf("Account deleted \n");
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
}

void freeAll(NODE *ptr) // in option 0
{
    if (ptr == NULL)
    {
        printf("List is already empty\n");
        return;
    }
    else
    {
        freeAll(ptr->next);
        free(ptr);
    }
}

void showTransactions(NODE *ptr) // option6
{
    char nameInput[50];
    int enteredPin;
    int found = 0;

    if (ptr == NULL)
    {
        printf("\nNo account to show\n");
        return;
    }

    printf("Enter account name to show transactions: \n");
    scanf("%50s", nameInput);

    while (ptr != NULL)
    {
        if (strcmp(ptr->data.name, nameInput) == 0)
        { // check if name is in list and matches
            found = 1;
            printf("Enter pin number: \n");
            scanf("%d", &enteredPin);
            if (ptr->data.pin == enteredPin)
            {
                if (ptr->data.totalTransactions == 0)
                {
                    printf("No transactions in your account\n");
                    return;
                }
                else
                {
                    printf("Here are your transactions: \n");
                    for (int i = 0; i < ptr->data.totalTransactions; i++)
                    {
                        printf("%d: Type: %s, Amount: $%.2lf\n", i + 1, ptr->data.transactions[i].type, ptr->data.transactions[i].amount);
                    }
                    return;
                }
            }
            else
            {
                printf("\nWrong pin\n");
                break;
            }
        }
        ptr = ptr->next;
    }
    if (!found)
    {
        printf("\nAccount name not found or typed wrong\n");
    }
}
