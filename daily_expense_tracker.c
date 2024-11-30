//Daily Expense Tracker Project

/*Functional Requirements
Here are 100 functional requirements divided into categories for clarity:

Basic Functionalities
Add a new expense.
Edit an existing expense.
Delete an expense.
List all expenses.
Filter expenses by date.
Filter expenses by category.
View total expenses.
View expenses for a specific period.
Save expenses to a file.
Load expenses from a file.

# Categories and Tags

Add categories for expenses.
Edit categories.
Delete categories.
Tag expenses for easy searching.
Search expenses by tag.

User Accounts

Create a user account.
Edit user account details.
Delete a user account.
Switch between multiple users.
View total expenses by user.

Reports

Generate monthly expense reports.
Generate weekly expense reports.
Generate daily expense reports.
Export reports to a file.
View top spending categories.

Budget Management

Set a monthly budget.
Track budget progress.
Warn when exceeding the budget.
View remaining budget.
Reset budget for the next month.

Security

Set a PIN for the application.
Change the application PIN.
Lock the application after inactivity.
Require PIN to delete an expense.
Encrypt saved expense data.

Usability

View expenses in a table format.
Add notes to an expense.
Sort expenses by amount.
Sort expenses by date.
Use keyboard shortcuts for actions.

Advanced Features

Automatically categorize expenses.
Track recurring expenses.
Merge duplicate expenses.
Handle currency conversion.
View daily average spending.

Notifications

Notify about upcoming recurring expenses.
Notify when nearing budget limit.
Remind to add daily expenses.
Notify of large expenditures.
Notify of unused budget.

Data Management

Import expenses from another system.
Export expenses to another system.
Archive old expenses.
Delete all data (reset system).
Validate data integrity.

User Interface

Display recent expenses on the home screen.
Use colored indicators for budget status.
Allow custom date formats.
Show help text for new users.
Display welcome message.

Categories Extension

Support for nested categories.
Show category usage statistics.
Allow merging categories.
View unused categories.
Enable custom category colors.

Graphical Insights

Display spending trends in a chart.
Show category-wise expense distribution.
Visualize budget progress.
Highlight anomalies in spending.
Provide comparative insights.

Multi-Device Features

Sync expenses across devices.
Allow guest users with limited features.
Add reminders for expense entry.
Allow multiple users per device.
Enable expense sharing between users.

Error Handling

Handle invalid inputs gracefully.
Alert for missing mandatory fields.
Provide undo functionality.
Log system errors.
Retry failed actions.

Internationalization

Support multiple currencies.
Allow custom language settings.
Adjust date formats regionally.
Use metric or imperial system.

Extensibility

Add plugins for new features.
Customize interface themes.
Allow third-party integrations.
Enable API access for automation.
Support expense classification via AI.

Backup and Restore

Backup expense data manually.
Schedule automatic backups.
Restore data from backup.
Export backup to external devices.

Advanced Reports

Show savings trends.
Forecast future expenses.
Compare spending against peers.
Provide customized report formats.
Highlight under-utilized budgets.
Show ROI on investments.
Calculate potential savings. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_CATEGORY_LEN 50
#define MAX_NOTE_LEN 100

typedef struct {
    char date[11]; // Format: YYYY-MM-DD
    char category[MAX_CATEGORY_LEN];
    float amount;
    char note[MAX_NOTE_LEN];
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// Function prototypes
void addExpense();
void listExpenses();
void saveExpensesToFile();
void loadExpensesFromFile();

int main() {
    int choice;

    loadExpensesFromFile();

    while (1) {
        printf("\nDaily Expense Tracker\n");
        printf("1. Add Expense\n");
        printf("2. List Expenses\n");
        printf("3. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                listExpenses();
                break;
            case 3:
                saveExpensesToFile();
                printf("Expenses saved. Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Error: Maximum expense limit reached.\n");
        return;
    }

    Expense newExpense;

    printf("Enter date (YYYY-MM-DD): ");
    fgets(newExpense.date, sizeof(newExpense.date), stdin);
    newExpense.date[strcspn(newExpense.date, "\n")] = '\0';

    printf("Enter category: ");
    fgets(newExpense.category, sizeof(newExpense.category), stdin);
    newExpense.category[strcspn(newExpense.category, "\n")] = '\0';

    printf("Enter amount: ");
    scanf("%f", &newExpense.amount);
    getchar(); // Clear newline character

    printf("Enter note: ");
    fgets(newExpense.note, sizeof(newExpense.note), stdin);
    newExpense.note[strcspn(newExpense.note, "\n")] = '\0';

    expenses[expenseCount++] = newExpense;
    printf("Expense added successfully!\n");
}

void listExpenses() {
    if (expenseCount == 0) {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("\n%-15s %-20s %-10s %-30s\n", "Date", "Category", "Amount", "Note");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < expenseCount; i++) {
        printf("%-15s %-20s %-10.2f %-30s\n", expenses[i].date, expenses[i].category, expenses[i].amount, expenses[i].note);
    }
}

void saveExpensesToFile() {
    FILE *file = fopen("expenses.txt", "w");
    if (!file) {
        printf("Error: Could not save expenses to file.\n");
        return;
    }

    for (int i = 0; i < expenseCount; i++) {
        fprintf(file, "%s|%s|%.2f|%s\n", expenses[i].date, expenses[i].category, expenses[i].amount, expenses[i].note);
    }

    fclose(file);
}

void loadExpensesFromFile() {
    FILE *file = fopen("expenses.txt", "r");
    if (!file) {
        return; // No file to load
    }

    while (!feof(file) && expenseCount < MAX_EXPENSES) {
        Expense exp;
        if (fscanf(file, "%10[^|]|%49[^|]|%f|%99[^\"]\n", exp.date, exp.category, &exp.amount, exp.note) == 4) {
            expenses[expenseCount++] = exp;
        }
    }

    fclose(file);
}
