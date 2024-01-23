// Include libraries
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// Define color codes
#define red "\033[31m"
#define green "\033[32m"
#define yellow "\033[33m"
#define blue "\033[34m"
#define cyan "\033[36m"
#define reset "\033[0m"
// Define font format
#define bold "\033[1m"

// Define structs & typedef
typedef struct account_info
{
    unsigned account_number;
    char username[30];
    unsigned balance;
    char password[5];
} account_info;

typedef struct transaction_info
{
    unsigned account_number;
    char type[20];
    unsigned amount;
    time_t timestamp;
} transaction_info;

// Global Variable
char choice;
unsigned amount;
unsigned account_number;
char password[5];
account_info login_account;
transaction_info transaction;

// Function Prototypes
void Account_Holder_Menu(unsigned option);
void Account_Information();
void Account_Menu(unsigned option);
void Admin_Login();
void Admin_Login_Menu(unsigned option);
void Create_New_Account();
void Credit();
void Delete_Account();
void Deposit_Cash();
int Is_Account_Exists(unsigned accountNumber);
void Help_And_Feedback();
void Loading();
void Login_Account();
void Logout();
void Main_Menu(unsigned option);
void Money_Transfer();
void Password(char password[]);
void Suspend_Any_Account();
void Transactions_History();
void Update_Balance(unsigned account_number, unsigned new_balance, const char *type, unsigned amount);
void View_All_Accounts();
void View_Account_Details();
void View_Transactions_History();
void Withdraw_Cash();

/*
    Menu Selection:
    In each menu;
    up (w), down (s), Enter and escape (esc).
    After getting key, if it is up or down, same menu function is called recursively
    with the option up or down. If the key is "Enter", menu function corresponding to option
    is called with default option as 0. If "escape" key is pressed, previous menu function
    is called with option/position of current menu in the previous menu. For an invalid key press
    (Default), the current menu function will be called, keeping you on the same option.

    Menu Highlighting:
    defined color is used which gives a unique color to selected option
    based on the value of option. These defined colors have also been
    used in coloring specific text outputs in various locations throughout the program.

    Clear Screen:
    system("cls") function is a build-in library function which is used many time in
    program to clear screen and continue program.
*/

// Main Function.......
int main()
{
    Main_Menu(0); // call Main_Menu function

    return 0;
}

// Function: Managing the main menu of the bank management system
void Main_Menu(unsigned option)
{

    system("cls");

    printf(red bold "\n\n\t\t\tBANK MANAGEMENT SYSTEM");

    printf("\n\n\n\n");
    printf(option == 0 ? blue bold : reset);
    printf("\tACCOUNT HOLDER\n\n");
    printf(option == 1 ? blue bold : reset);
    printf("\tADMIN LOGIN\n\n");
    printf(option == 2 ? blue bold : reset);
    printf("\tCREDIT\n\n");

    printf(yellow bold);
    printf("\n\n\n\n\n\n\n");
    printf("\t < W: Up >  < S: Down >  < Enter: Select >  < Esc: Previous Menu >");

    switch (_getch())
    {
    case 'w':
    case 'W':
    case 72:
        if (option == 0)
            Main_Menu(2);
        else
            Main_Menu(--option);
        break;
    case 's':
    case 'S':
    case 80:
        Main_Menu(++option % 3);
        break;
    case '\r':
        switch (option)
        {
        case 0:
            Account_Holder_Menu(0);
            break;
        case 1:
            Admin_Login();
            break;
        case 2:
            Credit();
            break;
        default:
            break;
        }
    default:
        Main_Menu(option);
        break;
    }
}

// Function: Where a person can create account or login his account
void Account_Holder_Menu(unsigned option)
{
    system("cls");
    printf("\n\n\n\n\n\n");
    printf(option == 0 ? blue bold : reset);
    printf("\tCREATE NEW ACCOUNT\n\n");
    printf(option == 1 ? blue bold : reset);
    printf("\tACCOUNT LOGIN\n\n");
    printf(option == 2 ? blue bold : reset);
    printf("\tHELP AND FEEDBACK\n\n");

    switch (_getch())
    {
    case 'w':
    case 'W':
    case 72:
        if (option == 0)
            Account_Holder_Menu(2);
        else
            Account_Holder_Menu(--option);
        break;
    case 's':
    case 'S':
    case 80:
        Account_Holder_Menu(++option % 3);
        break;
    case '\r':
        switch (option)
        {
        case 0:
            Create_New_Account();
            Account_Holder_Menu(0);
            break;
        case 1:
            Login_Account();
            break;
        case 2:
            Help_And_Feedback();
            break;
        default:
            break;
        }
        break;
    case 27:
        Main_Menu(0);
        break;
    default:
        Account_Holder_Menu(option);
    }
}

// Function: Creating a new bank account
void Create_New_Account()
{
    account_info newAccount;
    char c_password[5];

    FILE *ptr;
    ptr = fopen("Accounts Information.Csv", "a");

    system("cls");
    printf(yellow);

    printf("\n\n\tEnter the account number: ");
    if (scanf("%u", &newAccount.account_number) != 1)
    {
        printf(red "\n\n\tError: Invalid Account Number\n");
        printf(yellow "\tPress any key to retry...\n");
        _getch();
        fflush(stdin);
        Create_New_Account();
    }
    else if (Is_Account_Exists(newAccount.account_number) == 1)
    {
        printf(red "\n\n\tAccount  already exists.\n");
        printf(yellow "\tPress Enter to retry or Esc to go back...\n");
        choice = _getch();
        fflush(stdin);

        if (choice != '\r')
        {
            fclose(ptr);
            Account_Holder_Menu(0);
        }
        else
        {
            Create_New_Account();
        }
    }

    while (1)
    {
        printf(yellow "\tCreate a 4-digit password: ");
        Password(newAccount.password);

        printf("\tConfirm password: ");
        Password(c_password);

        if (strcmp(c_password, newAccount.password) != 0)
            printf(red "\n\tPassword not matches...\n");
        else
            break;
    }

    fflush(stdin);
    printf("\tCreate a Username: ");
    gets(newAccount.username);

    while (1)
    {
        printf("\n\tEnter the current balance: Rs.");
        if (scanf("%u", &newAccount.balance) != 1)
        {
            fflush(stdin);
            printf(red "\n\n\tError: Please enter a valid amount.\n");
            printf(yellow "\tPress any key to retry...\n");
            _getch();
        }
        else
            break;
    }

    printf(yellow "\n\tConfirm creating account? (Y/N): ");
    scanf(" %c", &choice);
    switch (choice)
    {
    case 'y':
    case 'Y':
        break;
    default:
        Account_Holder_Menu(0);
    }

    Loading();

    // Storing data in file to create account
    fprintf(ptr, "%u, %s,", newAccount.account_number, newAccount.username);
    fprintf(ptr, "%s,%u\n", newAccount.password, newAccount.balance);
    fclose(ptr);

    printf(green "\tAccount Created!\n");
    printf(yellow "\tPress any key to continue...\n");
    _getch();
    Account_Holder_Menu(0);
}

// Function: Check whether the account exist on same account number or not
int Is_Account_Exists(unsigned accountNumber)
{
    FILE *ptr;
    ptr = fopen("Accounts Information.Csv", "r");

    while (fscanf(ptr, "%u,", &account_number) == 1)
    {
        if (account_number == accountNumber)
        {
            fclose(ptr);
            return 1;
        }
        fscanf(ptr, "%*[^\n]\n"); // Skip the rest of the line
    }
    fclose(ptr);
    return 0;
}

// Function: To take input of 4-digits password from user
void Password(char password[])
{
    int i = 0;

    while (1)
    {
        char ch = _getch();
        if (ch == '\r' && i == 4)
            break; // Check for Enter key and 4 digits
        else if (ch == 8 && i > 0)
        {
            printf("\b \b");
            i--;
        }
        else if (i < 4 && ch >= '0' && ch <= '9')
        { // Check for digit input and display stars
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

// Function: Display loading where it call
void Loading()
{
    printf(yellow "\n\n\tLoading");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 100000000; j++)
            ;
        printf(".");
    }
    printf("\n");
}

// Function: For account login
void Login_Account()
{
    unsigned account_number;
    char password[5];

    FILE *ptr;
    ptr = fopen("Accounts Information.Csv", "r");

    int accountFound = 0;

    system("cls");

    printf(yellow "\n\n\n\tEnter the account number: ");
    scanf("%u", &account_number);

    printf("\tEnter the account password: ");
    Password(password);

    while (fscanf(ptr, "%u,%29[^,],%4[^,],%u\n", &login_account.account_number, login_account.username, login_account.password, &login_account.balance) == 4)
    {
        if (login_account.account_number == account_number && strcmp(login_account.password, password) == 0)
        {
            accountFound = 1;
            break;
        }
    }

    if (accountFound == 0)
    {
        printf(red "\n\n\tError: Invalid account number or password\n");
        printf(yellow "\tPress ENTER to retry or ESC to go back to the Account Holder Menu...\n");

        choice = _getch();
        fflush(stdin);

        if (choice != '\r')
        {
            fclose(ptr);
            Account_Holder_Menu(1);
        }
        else
        {
            Login_Account();
        }
    }

    fclose(ptr);

    printf(green "\n\n\tYou are Logged in!\n");
    printf(yellow "\tPress any key to continue...\n");
    _getch();
    Account_Menu(0);
}

// Function: To display Account Menu
void Account_Menu(unsigned option)
{
    system("cls");
    printf("\n\n\n");
    printf(yellow "\tACCOUNT NUMBER:" green " %u", login_account.account_number);
    printf(yellow "\t\tUSERNAME:" green " %s", login_account.username);
    printf(yellow "\t\tBALANCE:" green " %u PKR\n\n", login_account.balance);

    printf(option == 0 ? blue bold : reset);
    printf("\tACCOUNT INFORMATION\n\n");
    printf(option == 1 ? blue bold : reset);
    printf("\tDEPOSIT MONEY\n\n");
    printf(option == 2 ? blue bold : reset);
    printf("\tWITHDRAW MONEY\n\n");
    printf(option == 3 ? blue bold : reset);
    printf("\tMONEY TRANSFER\n\n");
    printf(option == 4 ? blue bold : reset);
    printf("\tSHOW TRANSACTION HISTORY\n\n");
    printf(option == 5 ? blue bold : reset);
    printf("\tDELETE ACCOUNT\n\n");
    printf(option == 6 ? blue bold : reset);
    printf("\tLOGOUT\n\n");

    switch (_getch())
    {
    case 'w':
    case 'W':
    case 72:
        if (option == 0)
            Account_Menu(6);
        else
            Account_Menu(--option);
        break;
    case 's':
    case 'S':
    case 80:
        Account_Menu(++option % 7);
        break;
    case '\r':
        switch (option)
        {
        case 0:
            Account_Information();
            break;
        case 1:
            Deposit_Cash();
            break;
        case 2:
            Withdraw_Cash();
            break;
        case 3:
            Money_Transfer();
            break;
        case 4:
            Transactions_History();
            break;
        case 5:
            Delete_Account();
            break;
        case 6:
            Logout();
            Account_Holder_Menu(1);
            break;
        default:
            break;
        }
        break;
    default:
        Account_Menu(option);
    }
}

// Function: Display information to user of his account
void Account_Information()
{
    system("cls");
    printf("\n\n\n\n");

    printf(cyan "\tACCOUNT NUMBER      :" green " %u\n\n", login_account.account_number);
    printf(cyan "\tACCOUNT HOLDER NAME :" green "%s\n\n", login_account.username);
    printf(cyan "\tBALANCE             :" green " %u PKR\n\n", login_account.balance);

    printf(yellow "\n\n\tPress any key to continue...");
    _getch();
    Account_Menu(0);
}

// Function: To deposit money
void Deposit_Cash()
{
    system("cls");
    printf("\n\n\n");
    printf(yellow "\tBALANCE:" green " %u PKR\n\n\n", login_account.balance);

    printf(yellow "\tEnter the amount to deposit: Rs. ");
    if (scanf("%u", &amount) != 1)
    {
        fflush(stdin);
        printf(red "\n\n\tError: Please enter a valid amount.\n");
        printf(yellow "\tPress any key to retry...");
        _getch();
        Deposit_Cash();
    }

    printf("\n\n\tConfirm the transaction? (Y/N): ");
    scanf(" %c", &choice);
    switch (choice)
    {
    case 'y':
    case 'Y':
        break;
    default:
        Account_Menu(1);
    }

    login_account.balance += amount;

    Update_Balance(login_account.account_number, login_account.balance, "Deposit", amount);
    printf(green "\n\n\tMoney Deposited!\n");
    printf("\tYour new balance is %u.\n", login_account.balance);
    printf(yellow "\tPress any key to continue...");
    _getch();
    Account_Menu(1);
}

// Function: To withdraw money
void Withdraw_Cash()
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(yellow "\tBALANCE:" green " %u PKR\n\n\n", login_account.balance);

        printf(yellow "\tEnter the amount to withdraw: Rs. ");
        if (scanf("%u", &amount) != 1)
        {
            fflush(stdin);
            printf(red "\n\n\tError: Please enter a valid amount.\n");
            printf(yellow "\tPress any key to retry...");
            _getch();
            Withdraw_Cash();
        }

        printf("\n\n\tConfirm the transaction? (Y/N): ");
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'y':
        case 'Y':
            break;
        default:
            Account_Menu(2);
        }

        if (amount > login_account.balance)
        {
            printf(red "\n\n\tError: Insufficient funds for the transaction.\n");
            printf(yellow "\tPress any key to retry...");
            _getch();
            fflush(stdin);
            continue;
        }
        else if (amount > login_account.balance / 1.5)
        {
            printf(red "\n\n\tError: Transaction limit exceeded.\n");
            printf(yellow "\tPress any key to retry...");
            _getch();
            fflush(stdin);
            continue;
        }
        else if (amount % 500 != 0)
        {
            printf(red "\n\n\tError: Amount must be in increments of 500.\n");
            printf(yellow "\tPress any key to retry...");
            _getch();
            fflush(stdin);
            continue;
        }
        else
        {
            login_account.balance -= amount;
            break;
        }
    }

    Update_Balance(login_account.account_number, login_account.balance, "Withdraw", amount);
    printf(green "\n\n\tMoney Withdrawn!\n");
    printf("\tYour new balance is %u\n.", login_account.balance);
    printf(yellow "\tPress any key to continue...");
    _getch();
    Account_Menu(2);
}

// Function: To Transfer money
void Money_Transfer()
{
    account_info recipient_account;

    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(yellow "\tBALANCE:" green " %u PKR\n\n\n", login_account.balance);

        printf(yellow);
        printf("\tEnter the recipient's account number: ");
        scanf("%u", &account_number);

        if (Is_Account_Exists(account_number) == 0)
        {
            printf(red "\n\n\tError: Account does not exist.\n");
            printf(yellow "\tPress ENTER to retry or ESC to go back to the Account Holder Menu...\n");
            choice = _getch();
            fflush(stdin);

            if (choice != '\r')
                Account_Menu(3);
            else
                continue;
        }
        else if (account_number == login_account.account_number)
        {
            printf(red "\n\n\tError: Unable to perform action. Recipient account matches the login account.\n");
            printf(yellow "\tPress ENTER to retry or ESC to go back to the Account Holder Menu...\n");
            choice = _getch();
            fflush(stdin);

            if (choice == '\r')
                Money_Transfer();
            else
                Account_Menu(3);
        }

        while (1)
        {
            printf("\tEnter the amount to transfer: Rs.");
            if (scanf("%u", &amount) != 1)
            {
                fflush(stdin);
                printf(red "\n\n\tError: Please enter a valid amount.\n");
                printf(yellow "\tPress any key to retry...\n");
                _getch();
            }
            else
                break;
        }

        printf("\n\n\tConfirm the transaction? (Y/N): ");
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'y':
        case 'Y':
            break;
        default:
            Account_Menu(3);
        }

        if (amount > login_account.balance)
        {
            printf(red "\n\n\tError: Insufficient funds for the transaction.\n");
            printf(yellow "\tPress any key to retry...");
            _getch();
            fflush(stdin);
            continue;
        }
        else
        {
            login_account.balance -= amount;
            break;
        }
    }

    Update_Balance(login_account.account_number, login_account.balance, "Money Transfer", amount);

    // Update the recipient's account balance
    FILE *ptr;
    ptr = fopen("Accounts Information.Csv", "r");

    while (fscanf(ptr, "%u,%29[^,],%4[^,],%u\n", &recipient_account.account_number, recipient_account.username, recipient_account.password, &recipient_account.balance) == 4)
    {
        if (recipient_account.account_number == account_number)
        {
            recipient_account.balance += amount;
            fclose(ptr);
            break;
        }
    }

    Update_Balance(recipient_account.account_number, recipient_account.balance, "Money Received", amount);
    printf(green "\n\n\tSuccessfully transferred funds to %u.\n", account_number);
    printf("\tYour new balance is %u.\n", login_account.balance);
    printf(yellow "\tPress any key to continue...");
    _getch();
    Account_Menu(3);
}

// Function: To update balance after transaction and log transaction
void Update_Balance(unsigned account_number, unsigned new_balance, const char *type, unsigned amount)
{
    FILE *accountsPtr, *tempPtr, *transactionsPtr;
    account_info temp_account;

    accountsPtr = fopen("Accounts Information.Csv", "r");
    tempPtr = fopen("temp.Csv", "w");
    transactionsPtr = fopen("Transactions.Csv", "a");

    while (fscanf(accountsPtr, "%u,%29[^,],%4[^,],%u\n", &temp_account.account_number, temp_account.username, temp_account.password, &temp_account.balance) == 4)
    {
        if (temp_account.account_number == account_number)
        {
            fprintf(tempPtr, "%u,%s,%s,%u\n", temp_account.account_number, temp_account.username, temp_account.password, new_balance);

            // Log the transaction
            transaction.account_number = account_number;
            strcpy(transaction.type, type);
            transaction.amount = amount;
            transaction.timestamp = time(NULL);
            fprintf(transactionsPtr, "%u,%s,%u,%ld\n", transaction.account_number, transaction.type, transaction.amount, transaction.timestamp);
        }
        else
        {
            fprintf(tempPtr, "%u,%s,%s,%u\n", temp_account.account_number, temp_account.username, temp_account.password, temp_account.balance);
        }
    }

    fclose(accountsPtr);
    fclose(tempPtr);
    fclose(transactionsPtr);

    remove("Accounts Information.Csv");
    rename("temp.Csv", "Accounts Information.Csv");
}

// Function: To see transactions history
void Transactions_History()
{
    system("cls");
    printf("\n\n");
    printf(yellow "\tACCOUNT NUMBER:" green " %u\n\n", login_account.account_number);

    FILE *transactionsPtr;

    transactionsPtr = fopen("Transactions.Csv", "r");

    if (transactionsPtr == NULL)
    {
        printf(red "\n\n\tNo transactions history available.\n");
    }
    else
    {
        printf(yellow);
        printf("  --------------------------------------------------------------------------------\n");
        printf("           TYPE                    AMOUNT                        TIMESTAMP\n");
        printf("  --------------------------------------------------------------------------------\n");

        while (fscanf(transactionsPtr, "%u,%19[^,],%u,%ld\n", &transaction.account_number, transaction.type, &transaction.amount, &transaction.timestamp) == 4)
        {
            if (transaction.account_number == login_account.account_number)
            {
                printf(cyan "   \t%-20s", transaction.type);
                printf((strcmp(transaction.type, "Money Received") == 0 || strcmp(transaction.type, "Deposit") == 0) ? green : red);
                printf("\t   Rs.%-20u", transaction.amount);
                printf(cyan "%-s\n", ctime(&transaction.timestamp));
            }
        }

        fclose(transactionsPtr);
    }

    printf(yellow "\n\n\tPress any key to continue ...");
    _getch();
    Account_Menu(4);
}

// Function: To delete your account
void Delete_Account()
{

    system("cls");

    printf(red "\n\n\n\n\tNote: Data recovery is not possible once the account has been deleted.\n");
    printf(yellow "\tAre you sure to delete account? (Y/N): ");
    scanf(" %c", &choice);
    switch (choice)
    {
    case 'y':
    case 'Y':
        break;
    default:
        Account_Holder_Menu(5);
    }

    FILE *accountsPtr, *tempPtr;
    account_info temp_account;

    accountsPtr = fopen("Accounts Information.Csv", "r");
    tempPtr = fopen("temp.Csv", "w");

    while (fscanf(accountsPtr, "%u,%29[^,],%4[^,],%u\n", &temp_account.account_number, temp_account.username, temp_account.password, &temp_account.balance) == 4)
    {
        if (temp_account.account_number != login_account.account_number)
        {
            fprintf(tempPtr, "%u,%s,%s,%u\n", temp_account.account_number, temp_account.username, temp_account.password, temp_account.balance);
        }
    }

    fclose(accountsPtr);
    fclose(tempPtr);

    remove("Accounts Information.Csv");
    rename("temp.Csv", "Accounts Information.Csv");

    Loading();
    printf(green "\tAccount %u has been permanently deleted.\n", login_account.account_number);
    printf(yellow "\tPress any key to continue...");
    _getch();
    Account_Holder_Menu(0);
}

//  Function: To logout account
void Logout()
{

    login_account.account_number = 0;
    login_account.balance = 0;
    login_account.password[0] = '\0';
    login_account.username[0] = '\0';

    transaction.account_number = 0;
    transaction.amount = 0;
    transaction.timestamp = 0;
    transaction.type[0] = '\0';

    printf(red "\n\n\tLogged out!\n");
    printf(yellow "\tPress any key to continue...\n");
    _getch();
}

// Function: Providing help and feedback to assist the user
void Help_And_Feedback()
{
    system("cls");
    printf("\n");

    printf(reset yellow "\tHELP:\n");

    printf(bold yellow "\t1. Account Creation:\n");
    printf("\t   - When creating a new account, enter a unique account number.\n");
    printf("\t   - 4-digit password should contain integers only\n");
    printf("\t   - Provide accurate details and confirm the creation.\n");
    printf("\t   - You are not allowed to  change name and password after account creation.\n\n");

    printf(yellow "\t2. Account Login:\n");
    printf("\t   - Use your account number and password to log in securely.\n");
    printf("\t   - Ensure the correctness of the account number and password.\n\n");

    printf(yellow "\t3. Deposit Money:\n");
    printf("\t   - Enter the amount you wish to deposit and confirm the transaction.\n");
    printf("\t   - Ensure sufficient funds for a successful deposit.\n\n");

    printf(yellow "\t4. Withdraw Money:\n");
    printf("\t   - Enter the amount you wish to withdraw and confirm the transaction.\n");
    printf("\t   - You are unable to withdraw money more than 65 percent of your balance.\n");
    printf("\t   - Withdrawals must be in increments of 500.\n\n");

    printf(yellow "\t5. Money Transfer:\n");
    printf("\t   - Enter the recipient's account number and the amount to transfer.\n");
    printf("\t   - Confirm the transaction and ensure sufficient funds.\n");
    printf("\t   - Transaction limits apply to money transfers.\n\n");

    printf(yellow "\t6. Show Transaction History:\n");
    printf("\t   - View a detailed history of your transactions.\n");
    printf("\t   - Check transaction types, amounts, and timestamps.\n\n");

    printf(yellow "\t7. Logout:\n");
    printf("\t   - Log out of your account for security purposes.\n\n");

    printf(reset yellow "\n\tFEEDBACK:\n");
    printf(bold yellow "\tWe value your feedback! If you have any suggestions or issues, please contact us.\n");
    printf("\tEmail: support@yourbank.com\n");
    printf("\tPhone: 123-456-7890\n");

    printf(yellow "\n\n\tPress any key to continue...\n");
    _getch();
    Account_Holder_Menu(2);
}

// Function: login restricted to admin only
void Admin_Login()
{
    char real_password[5] = "5911";

    system("cls");
    printf("\n\n\n");

    printf(red "\tNOTE: Access to the Admin Account is Prohibited..\n\n\n");

    printf(yellow "\tEnter admin pin: ");
    Password(password);

    if (strcmp(password, real_password) != 0)
    {
        printf(red "\n\n\tInvalid Password\n");
        _getch();
        Main_Menu(1);
    }

    printf(green);
    printf("\n\n\tYou are Logged in!\n");
    printf(yellow "\tPress any key to continue...\n");
    _getch();

    Admin_Login_Menu(0);
}

// Function: Login menu restricted to Admin Only
void Admin_Login_Menu(unsigned option)
{

    system("cls");
    printf("\n\n\n\n\n\n");

    printf(option == 0 ? blue bold : reset);
    printf("\tVIEW ALL ACCOUNTS\n\n");
    printf(option == 1 ? blue bold : reset);
    printf("\tVIEW TRANSACTIONS DETAILS\n\n");
    printf(option == 2 ? blue bold : reset);
    printf("\tSUSPEND ACCOUNT\n\n");
    printf(option == 3 ? blue bold : reset);
    printf("\tLOGOUT\n\n");

    switch (_getch())
    {
    case 'w':
    case 'W':
    case 72:
        if (option == 0)
            Admin_Login_Menu(3);
        else
            Admin_Login_Menu(--option);
        break;
    case 's':
    case 'S':
    case 80:
        Admin_Login_Menu(++option % 4);
        break;
    case '\r':
        switch (option)
        {
        case 0:
            View_All_Accounts();
            break;
        case 1:
            View_Transactions_History();
            break;
        case 2:
            Suspend_Any_Account();
            break;
        case 3:
            Logout();
            Main_Menu(1);
            break;
        default:
            break;
        }
        break;
    default:
        Admin_Login_Menu(option);
    }
}

// Function: To view all accounts
void View_All_Accounts()
{

    FILE *ptr;
    ptr = fopen("Accounts Information.Csv", "r");

    system("cls");
    printf("\n\n");

    if (ptr == NULL)
    {
        printf(red "\n\n\tNo Account Information Available\n");
    }
    else
    {
        printf(yellow);
        printf("  --------------------------------------------------------------------------\n");
        printf("    ACCOUNT NUMBER                     NAME                     BALANCE\n");
        printf("  --------------------------------------------------------------------------\n");

        while (fscanf(ptr, "%u,%29[^,],%4[^,],%u\n", &login_account.account_number, login_account.username, login_account.password, &login_account.balance) == 4)
        {
            printf(cyan "       \t%-20u\t   %-25s" green "\t Rs.%-10u\n", login_account.account_number, login_account.username, login_account.balance);
        }

        fclose(ptr);
    }

    printf(yellow "\n\n\tPress any key to continue ...");
    _getch();
    Admin_Login_Menu(0);
}

//  Function: To view transaction history
void View_Transactions_History()
{
    system("cls");
    printf("\n\n");

    FILE *transactionsPtr;

    transactionsPtr = fopen("Transactions.Csv", "r");

    if (transactionsPtr == NULL)
    {
        printf(red "\n\n\tNo transactions history available.\n");
    }
    else
    {
        printf(yellow);
        printf("  -------------------------------------------------------------------------------------------------\n");
        printf("      ACCOUNT NO.          TYPE                    AMOUNT                        TIMESTAMP\n");
        printf("  -------------------------------------------------------------------------------------------------\n");

        while (fscanf(transactionsPtr, "%u,%19[^,],%u,%ld\n", &transaction.account_number, transaction.type, &transaction.amount, &transaction.timestamp) == 4)
        {
            printf(cyan "   \t%-12u  \t%-18s\t   %-15u\t %-s\n", transaction.account_number, transaction.type, transaction.amount, ctime(&transaction.timestamp));
        }

        fclose(transactionsPtr);
    }

    printf(yellow "\n\n\tPress any key to continue ...");
    _getch();
    Admin_Login_Menu(1);
}

// Function to Suspend account
void Suspend_Any_Account()
{

    system("cls");

    printf(yellow "\n\n\n\n\n\tEnter the account number to suspend: ");
    scanf("%u", &account_number);

    if (Is_Account_Exists(account_number) == 0)
    {
        printf(red "\n\n\tError: Account does not exist.\n");
        printf(yellow "\tPress any key to continue...");
        _getch();
        Admin_Login_Menu(2);
    }
    else
    {
        printf(red "\n\n\tNote: Data recovery is not possible once the account has been suspended.\n");
        printf(yellow "\tAre you sure to suspend account? (Y/N): ");
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'y':
        case 'Y':
            break;
        default:
            Admin_Login_Menu(2);
        }
    }

    FILE *accountsPtr, *tempPtr;
    account_info temp_account;

    accountsPtr = fopen("Accounts Information.Csv", "r");
    tempPtr = fopen("temp.Csv", "w");

    while (fscanf(accountsPtr, "%u,%29[^,],%4[^,],%u\n", &temp_account.account_number, temp_account.username, temp_account.password, &temp_account.balance) == 4)
    {
        if (temp_account.account_number != account_number)
        {
            fprintf(tempPtr, "%u,%s,%s,%u\n", temp_account.account_number, temp_account.username, temp_account.password, temp_account.balance);
        }
    }

    fclose(accountsPtr);
    fclose(tempPtr);

    remove("Accounts Information.Csv");
    rename("temp.Csv", "Accounts Information.Csv");

    Loading();
    printf(green "\tAccount %u has been suspended.\n", account_number);
    printf(yellow "\tPress any key to continue...");
    _getch();
    Admin_Login_Menu(2);
}

// Function: To diplay name to give credit
void Credit()
{
    system("cls");
    printf("\n\n\n");
    printf(bold red "\tProgram Name:" cyan " Bank Management System\n");
    printf(bold red "\tVersion     :" cyan " 2.0\n");

    printf(bold red "\tAuthor      :" cyan " Muhammad Danish  (SE Student)\n");
    printf(bold red "\tEmail       :" cyan " mdanishateeq@gmail.com\n\n");

    printf(bold red "\tDescription :\n");
    printf(cyan "\tThis program  is a bank management system a university project developed in C language.\n\tIt includes several functions for management of bank accounts. This program provides a\n\trobust solution for efficient and secure banking operations.");

    printf(yellow "\n\n\tPress any key to continue ...");
    _getch();
    Main_Menu(2);
}
