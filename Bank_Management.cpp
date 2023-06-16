#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include <iomanip>
#include "Account.h"
using namespace std;


// printAccountList(listofAccount) outputs all accounts stored in listofAccount
void printAccountList(vector<Account>& listofAccount) {
    int totalAccount = listofAccount.size();
    if (totalAccount == 0) {
        cout << "There are currently no account on record." << "\n" << endl;
    } else {
        cout << "\nList of account names:" << endl;
        for (int i = 0; i < totalAccount; ++i) {
            cout << listofAccount[i].get_name() << endl;
        }
    }
}


// AccountSelector(listofAccount, message) reads input until a valid account is read
// and returns the position of the account in listofAccount
int AccountSelector(vector<Account>& listofAccount, const string& message) {
    string aName;
    int totalAccount = listofAccount.size();
    while (1) {
        cout << "\n" << message << endl;
        getline(cin, aName);
        while (aName.length() == 0) {
            cout << "Please enter an account. " << endl;
            getline(cin, aName);
        }
        if (aName == "-list") {
            printAccountList(listofAccount);
            continue;
        }
        for (int i = 0; i < totalAccount; ++i) {
            if (listofAccount[i].get_name() == aName) {
                return i;
            }
        }
        cout << "The account name you entered does not exist. Type \"-list\" for a list of existing account(s).\n";
    }
}


// CreateAccount(listofAccount) reads the name, account number and balance and 
// adds the account to listofAccount
void CreateAccount(vector<Account>& listofAccount) {
    string aName;
    double aBalance;
    int aNumber;
    int TotalAccount = listofAccount.size();
    int LoopControl = 1;

    cout << "\nPlease enter the account holder's name:" << endl;
    while (LoopControl) { 
        getline(cin, aName);
        if (aName.length() == 0) {
            cout << "Please enter a name." << endl;
            continue;
        } 
        for (int i = 0; i <= TotalAccount; ++i) {
            if (i == TotalAccount) {
                cout << "You entered: " << aName << endl;
                LoopControl = 0;
                break;
            }
            if (listofAccount[i].get_name() == aName) {
                cout << "\n" << aName << " already has an account. Please enter another account name." << endl;
                break;
            }
        }  
    }

    
    LoopControl = 1;
    while (LoopControl) {
        cout << "\nPlease enter an account number:" << endl;
        cin >> aNumber;
        if (cin.fail() || !(cin.eof() || cin.peek() == '\n')) {
            cout << "The account number cannot contain anything other than numbers.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } 
        for (int i = 0; i <= TotalAccount; ++i) {
            if (i == TotalAccount) {
                cout << "You entered: " << aNumber << endl;
                LoopControl = 0;
                break;
            }
            if (listofAccount[i].get_number() == aNumber) {
                cout << aNumber << " is already taken by another account.\n";
                break;
            }
        }
    }

    while (1) {
        cout << "\nPlease enter the account's balance:" << endl;
        cin >> aBalance;
        if (cin.fail() || !(cin.eof() || cin.peek() == '\n')) {
            cout << "That is not a valid balance number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            continue;
        } else if (aBalance < 0){
            cout << "Account balance cannot be negative.\n";
            continue;
        } else {
            cout << "You entered: " << aBalance << endl << endl;
            break;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    listofAccount.push_back(Account(aName, aBalance, aNumber));
    cout << "The account has been added!\n" << endl;
}


// AddTransaction (listofAccount) reads the type and amount of the transaction then make and document 
// the transaction if the account has sufficient balance
void AddTransaction (vector<Account>& listofAccount) {
    string aName;
    int totalAccount = listofAccount.size();
    double amount;
    string type;
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the account that you'd like to make a transaction for:");
    cout << "Making transaction for: " << listofAccount[AccountIndex].get_name() << "." << endl;
    cout << "Be aware that the system only saves the most recent 20 transactions! "
            "The oldest transaction record will be replaced if there are already 20 transactions saved." << endl;

    while (1) {
        cout << "\nPlease enter the type of this transaction:" << endl;
        getline(cin, type);
        if (type.length() == 0) {
            cout << "The transaction type cannot be empty.\n";
            continue;
        } else {
            cout << "You entered: " << type << endl;
            break;
        }
    }

    while (1) {
        cout << "\nPlease enter the amount of this transaction (enter a negative number for withdrawal):" << endl;
        cin >> amount;
        if (cin.fail() || !(cin.eof() || cin.peek() == '\n')) {
            cout << "That was not a valid amount." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (amount < 0.01 && amount > -0.01) {
            cout << "The transaction amount cannot be lower than 0.01$!";
            continue;
        } else if (listofAccount[AccountIndex].get_balance() < -amount) {
            cout << "the account does not have enough balance to complete the transaction. ";
            cout << "current balance: " << listofAccount[AccountIndex].get_balance() << endl;
            continue;
        } else {
            cout << "You entered: " << amount << endl;
            break;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    listofAccount[AccountIndex].add_transaction(type, amount);
    listofAccount[AccountIndex].change_balance(amount);
    cout << "Transation successfully made! Current account balance: " << listofAccount[AccountIndex].get_balance() << endl << endl;
}


// printAccountSummary(listofAccount) outputs the account's information 
// (name, account number, balance, transaction history)
void printAccountSummary(vector<Account>& listofAccount) {
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the account that you'd like to print:");
    cout << "\n";
    listofAccount[AccountIndex].print_summary(cout);
}


// generateAccountSummary(listofAccount) outputs a .txt file containing the account's information
// (name, account number, balance, transaction history)
void generateAccountSummary(vector<Account>& listofAccount) {
    string fileName;
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the account that you'd like to print:");
    cout << "Generating account summary for: " << listofAccount[AccountIndex].get_name() << ".\n\n";
    cout << "Please enter a name for the summary file:" << endl;
    getline(cin, fileName);
    
    string generatedFileName = fileName + ".txt";
    ofstream summary(generatedFileName);
    listofAccount[AccountIndex].print_summary(summary);
    summary.close();

    cout << "The account summary has been generated as " << fileName << ".txt!\n" << endl;    
}


// ClearTransaction(listofAccount) empties the transaction history saved on the account;
// Does not affect the current balance of the account modified by the transactions made
void ClearTransaction (vector<Account>& listofAccount) {
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the account that you'd like to clear the transaction for:");
    listofAccount[AccountIndex].clear_transaction();
    cout << listofAccount[AccountIndex].get_name() << "'s transaction history has been cleared!\n" << endl;
}


// DeleteAccount(listofAccount) removes the account from listofAccount
void DeleteAccount (vector<Account>& listofAccount) {
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the account that you'd like to delete:");
    listofAccount.erase(listofAccount.begin() + AccountIndex);
    cout << "\nThe account has been deleted.\n" << endl;
}


// printOverview(listofAccount, ostr) outputs the name, number and balance of every account on record
// to the given output stream
void printOverview(vector<Account>& listofAccount, ostream& ostr) {
    int totalAccount = listofAccount.size();
    ostr << "Account Overview\n" << endl;
    for (int i = 0; i < totalAccount; ++i) {
        ostr << "Account " << (i + 1) << endl;
        ostr << "   Name: " << listofAccount[i].get_name() << endl;
        ostr << "   Number: " << listofAccount[i].get_number() << endl;
        ostr << "   Balance: " << listofAccount[i].get_balance() << "\n" << endl; 
    }
}


// genereateOverview(listofAccount) outputs a .txt file that contains the name, number and balance of
// every account on record
void generateOverview(vector<Account>& listofAccount) {
    string fileName;
    cout << "\nPlease enter a name for the accounts overview file:" << endl;
    getline(cin, fileName);

    string generatedFileName = fileName + ".txt";
    ofstream summary(generatedFileName);
    printOverview(listofAccount, summary);
    summary.close();

    cout << "The accounts overview has been generated as " << fileName << ".txt!\n" << endl; 
}


// Confirmation(message) prompts the user to confirm/cancel their command and
// returns a bool based on the user input
bool Confirmation(const string& message) {
    string confirmation;
    cout << "\n" << message << endl;
    while (1) {
        cout << "Type \"yes\" or \"y\" to confirm, \"no\" or \"n\" otherwise." << endl;
        getline(cin, confirmation);
        if (confirmation == "yes" || confirmation == "y") {
            return true;
        } else if (confirmation == "no" || confirmation == "n") {
            return false;
        } else {
            cout << "Invalid input. ";
        }
    }
}



int main() {
    cout << fixed;
    cout << setprecision(2);
    vector<Account> listofAccount;
    string input;
    cout << "Welcome! ";
    while(1) {
        cout << "Please enter your command below. Type \"help\" for more information." << endl;
        getline(cin, input);

        if (input == "create") {
            CreateAccount(listofAccount);
        } 

        else if (input == "account summary" || input == "transaction" ||
                 input == "delete" || input == "generate account summary" ||
                 input == "clear transaction" || input == "account list" ||
                 input == "overview" || input == "generate overview") {
                    if (listofAccount.size() == 0) {
                        cout << "There are no account on record. Please create an account first." << "\n" << endl;
                    } else {
                        if (input == "account summary") {
                            printAccountSummary(listofAccount);
                        } else if (input == "generate account summary") {
                            generateAccountSummary(listofAccount);
                        } else if (input == "transaction") {
                            AddTransaction(listofAccount);
                        } else if (input == "delete") {
                            if (Confirmation ("Are you sure? Deleted accounts are not recoverable!")) {
                                DeleteAccount(listofAccount);
                            }
                        } else if (input == "clear transaction") {
                            if (Confirmation("Are you sure? Cleared account transactions are not recoverable!")) {
                                ClearTransaction(listofAccount);
                            }
                        } else if (input == "account list") {
                            printAccountList(listofAccount);
                            cout << endl;
                        } else if (input == "overview") {
                            cout << endl;
                            printOverview(listofAccount, cout);
                        } else if (input == "generate overview") {
                            generateOverview(listofAccount);
                        }
                    }
        }

        else if (input == "help") {
            cout << "\nHere's a list of commands that the current version supports:\n\n"
                    "create: creates a new account\n"
                    "account list: prints out a list of account names on record\n"
                    "transaction: adds a transaction to an account and changes the account's balance accordingly\n"
                    "account summary: prints the selected account's name, number, balance and transaction history to the console\n"
                    "generate account summary: same as account summary, but stores the output in a .txt file\n"
                    "overview: prints the account name, number and balance of every account on record to the console\n"
                    "generate overview: same as overview, but stores the output in a .txt file\n"
                    "clear transaction: clear the transaction history of an existing account\n"
                    "delete: deletes an existing account\n"                    
                    "q or quit: exits the program\n" << endl;
            
            cout << "Note that one user can hold at most one account at a time,"
                    "and no two accounts can have the same account number\n"
                    "In order to use any command that is not create or q/quit," 
                    "there must be at least one account on record\n" << endl;
        }
        
        else if (input == "") {
            continue;
        }

        else if (input == "quit" || input == "q") {
            break;
        } 
        
        else {
            cout << "\"" << input << "\" is not a valid command.\n" << endl;
            cin.clear();
        }
    }
}