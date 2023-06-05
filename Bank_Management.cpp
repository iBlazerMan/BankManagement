#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

class Account {
private:
    string name;
    double balance;
    int card_number;
    string transaction_type[20];
    double transaction_amount[20];

public:
    // constructor
    Account(const string& inp_name, double inp_balance, int inp_card_number) {
        name = inp_name;
        balance = inp_balance;
        card_number = inp_card_number;
        for (int i = 0; i < 20; ++i) {
            transaction_type[i] = "";
            transaction_amount[i] = 0;
        }
    }

    // returns the account's current balance
    double get_balance() {
        return balance;
    }

    // modify the current account's balance
    void change_balance(double amount) {
        balance = balance + amount;
    }

    // returns the account's name
    string get_name() {
        return name;
    }

    // returns card number
    int get_number() {
        return card_number;
    }

    // add a new transaction with type/amount
    void add_transaction(string type, double amount) {
        for (int i = 18; i >= 0; --i) {
            if (transaction_amount[i] != 0) {
                transaction_amount[i + 1] = transaction_amount[i]; 
                transaction_type[i + 1] = transaction_type[i];
            }
        }
        transaction_amount[0] = amount;
        transaction_type[0] = type;
    }

    void clear_transaction() {
        for (int i = 0; i < 20; ++i) {
            transaction_type[i] = "";
            transaction_amount[i] = 0;
        }
    }

    // prints the transactions recorded including the type and amount to the given output stream
    void printTransaction(ostream& ostr) {
        if (transaction_amount[0] == 0) {
            ostr << "There are no transaction on record." << "\n" << endl;
            return;
        }
        int i = 0;
        ostr << "Most recent transactions:" << endl;
        while (transaction_amount[i] != 0) { 
            ostr << "Transaction #" << (i + 1) << endl;
            ostr << "Transaction type: " << transaction_type[i] << endl;
            if (transaction_amount[i] > 0) {
                ostr << "Balance change: +" << transaction_amount[i];
            } else {
                ostr << "Balance change: " << transaction_amount[i];
            }
            ostr << "\n" << endl;
            i++;
        }
    }

    // generates a .txt file that contains all info of the account
    void generateAccountSummary(const string FileName) {
        string generatedFileName = FileName + ".txt";
        ofstream summary(generatedFileName);
        summary << "Name: " << get_name() << endl;
        summary << "Card Number: " << get_number() << endl;
        summary << "Current Balance: " << get_balance() << "\n" << endl;
        printTransaction(summary);
        summary.close();
    }
};

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
                cout << aNumber << " is already being used.\n";
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


void AddTransaction (vector<Account>& listofAccount) {
    string aName;
    int totalAccount = listofAccount.size();
    double amount;
    string type;
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the that you'd like to make a transaction for:");
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

void AccountSummary(vector<Account>& listofAccount) {
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the account that you'd like to print:");
    cout << "\n";
    listofAccount[AccountIndex].printTransaction(cout);
}

void PrintAccountSummary(vector<Account>& listofAccount) {
    string fileName;
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the account that you'd like to print:");
    cout << "Generating account summary for: " << listofAccount[AccountIndex].get_name() << ".\n\n";
    cout << "Please enter a name for the summary file:" << endl;
    getline(cin, fileName);
    listofAccount[AccountIndex].generateAccountSummary(fileName);
    cout << "The account summary has been generated as " << fileName << ".txt!" << "\n" << endl;    
}


void ClearTransaction (vector<Account>& listofAccount) {
    int AccountIndex = AccountSelector(listofAccount, 
    "Please enter the name of the account that you'd like to clear the transaction for");
    listofAccount[AccountIndex].clear_transaction();
    cout << listofAccount[AccountIndex].get_name() << "'s transaction history has been cleared!" << "\n" << endl;
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
        
        else if (input == "print account summary") {
            if (listofAccount.size() == 0) {
                cout << "There are no account on record. Please create an account first." << "\n" << endl;
            } else {
                PrintAccountSummary(listofAccount);
            }
        } 

        else if (input == "account summary") {
            if (listofAccount.size() == 0) {
                cout << "There are no account on record. Please create an account first." << "\n" << endl;
            } else {
                AccountSummary(listofAccount);
            }
        }

        else if (input == "transaction") {
            if (listofAccount.size() == 0) {
                cout << "There are no account to add transaction to. Please create an account first." << "\n" << endl;
            } else {
                AddTransaction(listofAccount);
            }
        }

        /*
        else if (input == "delete") {

        }
        */

        else if (input == "clear transaction") {
            if (listofAccount.size() == 0) {
                cout << "There are no account to add transaction to. Please create an account first." << "\n" << endl;
            }
            string confirmation;
            cout << "\n" << "Are you sure? Cleared account transactions are not recoverable!\n";
            while (1) {
                cout << "Type \"yes\" or \"y\" to confirm, \"no\" or \"n\" otherwise." << endl;
                getline(cin, confirmation);
                if (confirmation == "yes" || confirmation == "y") {
                    ClearTransaction(listofAccount);
                    break;
                } else if (confirmation == "no" || confirmation == "n") {
                    break;
                } else {
                    cout << "Invalid input. ";
                }
            }
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