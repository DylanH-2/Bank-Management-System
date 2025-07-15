#include "bankinghead.h"
#include <ctype.h>

NODE *head = NULL;
int main()
{

    srand(time(NULL)); // makes rand change every program run
    int option;
    while (1)
    {
        printf("\nPick an option \n");
        printf("Option 1: Create account \n");
        printf("Option 2: Show all accounts \n");
        printf("Option 3: Edit account \n");
        printf("Option 4: Withdraw or Deposit: \n");
        printf("Option 5: Delete account: \n");
        printf("Option 6: Show transactions: \n");
        printf("Option 0: Exit \n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("\nCreating account: \n");
            createAccount();
            break;

        case 2:
            printf("\nShowing all accounts: \n");
            showAccounts(head);
            break;

        case 3:
            printf("\nEditing account: \n");
            editAccount(head);
            break;

        case 4:
            withdrawOrDeposit(head);
            break;

        case 5:
            printf("\nDeleting account: \n");
            deleteAccount(head);
            break;

        case 6:
            printf("Showing transactions: \n");
            showTransactions(head);
            break;

        case 0:
            printf("\nExiting \n");
            freeAll(head);
            return 0;

        default:
            printf("\nInvalid choice \n");
        }
    }
}