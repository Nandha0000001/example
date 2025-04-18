#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a financial transaction
struct Transaction {
    int amount;
    char category[50];
    char date[11]; // Format: YYYY-MM-DD
    struct Transaction* next;
    struct Transaction* prev;
};

// Initialize the head of the doubly linked list
struct Transaction* head = NULL;

// Function to add a new transaction with category
void addTransaction(int amount, char* category,char* date) {
    struct Transaction* newTransaction = (struct Transaction*)malloc(sizeof(struct Transaction));
    newTransaction->amount = amount;
    strcpy(newTransaction->category, category);
    strcpy(newTransaction->date, date);
    newTransaction->next = NULL;
    newTransaction->prev = NULL;

    if (head == NULL) {
        head = newTransaction;
    } else {
        struct Transaction* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTransaction;
        newTransaction->prev = current;
    }
    printf("Transaction added successfully!");
}

// Function to delete a transaction based on amount and category
void deleteTransaction(int amount, char* category,char* date) {
    struct Transaction* current = head;
    while (current != NULL) {
        if (current->amount == amount && strcmp(current->category, category) == 0 &&
            strcmp(current->date, date) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            printf("Transaction  deleted successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Transaction  not found.\n");
}

// Function to display all transactions with categories
void displayTransactions() {
    struct Transaction* current = head;
    printf("Transactions:\n");
    while (current != NULL) {
        printf("Date: %s,Amount: %d, Category: %s\n", current->date, current->amount, current->category);
        current = current->next;
    }
}


// Function to edit a transaction
void editTransaction(int oldAmount, char* oldCategory, char* oldDate,
                     int newAmount, char* newCategory, char* newDate) {
    struct Transaction* current = head;
    while (current != NULL) {
        if (current->amount == oldAmount && strcmp(current->category, oldCategory) == 0 &&
            strcmp(current->date, oldDate) == 0) {
            current->amount = newAmount;
            strcpy(current->category, newCategory);
            strcpy(current->date, newDate);
            printf("Transaction updated successfully.\n");
            return;
        }
        current = current->next;
    }
     printf("Transaction not found.\n");
 }


// Function to display the sum of all transaction amounts
void displayTotalsavings() {
    struct Transaction* current = head;
    int total = 0;
    while (current != NULL) {
        total += current->amount;
        current = current->next;
    }
    printf("Total savings after all transactions: %d\n", total);
}


// Function to calculate and display INCOME and EXPENSE amount
void displayINCOMEandEXPENSES() {
    struct Transaction* current = head;
    int profit = 0, loss = 0;
    while (current != NULL) {
        if (current->amount > 0) {
            profit += current->amount;
        } else {
            loss += current->amount; // expense amounts are stored as negative
        }
        current = current->next;
    }
    printf("Total Credited amount: %d\n", profit);
    printf("Total Depited amount: %d\n", -loss); // expense  amount back to positive for display
}


int main() {
    int choice, amount, newAmount;
    char category[50], newCategory[50],oldCategory[50],date[11],newDate[11];
    while (1) {
        printf("\nPERSONAL FINANCE MANAGER\n");
        printf("1. Add Transaction\n");
        printf("2. Delete Transaction\n");
        printf("3. Display Transactions\n");
        printf("4. Edit Transaction\n");
        printf("5. Display Total Savings\n");
        printf("6. Display Income and Expense amount\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter transaction amount: ");
                scanf("%d", &amount);
                printf("Enter transaction category: ");
                scanf("%s", category);
                printf("Enter date of transaction: ");
                scanf("%s",date);
                addTransaction(amount, category,date);
                break;
            case 2:
                printf("Enter transaction amount to delete: ");
                scanf("%d", &amount);
                printf("Enter transaction category to delete: ");
                scanf("%s", category);
                printf("Enter date of transaction to delete: ");
                scanf("%s",date);
                deleteTransaction(amount, category,date);
                break;
            case 3:
                displayTransactions();
                break;
            case 4:
               printf("Enter the amount of the transaction you want to edit: ");
                scanf("%d", &amount);
                printf("Enter the category of the transaction you want to edit: ");
                scanf("%s", category);
                printf("Enter the date of the transaction you want to edit (YYYY-MM-DD): ");
                scanf("%s", date);
                printf("Enter the new amount: ");
                scanf("%d", &newAmount);
                printf("Enter the new category: ");
                scanf("%s", newCategory);
                printf("Enter the new date (YYYY-MM-DD): ");
                scanf("%s", newDate);
                editTransaction(amount, category, date, newAmount, newCategory, newDate);
                break;
            case 5:
                displayTotalsavings();
                break;
            case 6:
                displayINCOMEandEXPENSES();
                break;
            case 7:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
