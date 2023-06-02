#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
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

    // prints the transactions recorded including the type and amount to the given output stream
    void printTransaction(ostream& ostr) {
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
            ostr << endl << endl;
            i++;
        }
    }

    // generates a .txt file that contains all info of the account
    void generateAccountSummary(const string FileName) {
        string generatedFileName = FileName + ".txt";
        ofstream summary(generatedFileName);
        summary << "Name: " << get_name() << endl;
        summary << "Card Number: " << get_number() << endl;
        summary << "Current Balance: " << get_balance() << endl << endl;
        printTransaction(summary);
        summary.close();
    }

};

Account CreateAccount() {
    string aName;
    double aBalance;
    int aNumber;

    while (1) {
        cout << "Please enter the account holder's name:" << endl;
        getline(cin, aName);
        if (aName.length() == 0) {
            cout << "Please enter a name." << endl;
            continue;
        } else {
            cout << "You entered: " << aName << endl
                 << endl;
            break;
        }
    }

    while (1) {
        cout << "Please enter the account number:" << endl;
        cin >> aNumber;
        if (!cin.fail()) {
            cout << "You entered: " << aNumber << endl << endl;
            break;
        } else {
            cout << "That was not a valid account number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (1) {
        cout << "Please enter the account's balance:" << endl;
        cin >> aBalance;
        if (cin.fail()) {
            cout << "That was not a valid balance number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            continue;
        } else if (aBalance < 0){
            cout << "Account balance cannot be negative." << endl;
            continue;
        } else {
            cout << "You entered: " << aBalance << endl << endl;
            break;
        }
    }
    return Account(aName, aBalance, aNumber);
}

void AddTransaction (Account &account) {
    double amount;
    string type;
    while (1) {
        cout << "Please enter the type of this transaction:" << endl;
        getline(cin, type);
        if (type.length() == 0) {
            cout << "The transaction type cannot be empty." << endl;
            continue;
        } else {
            cout << "You entered: " << type << endl << endl;
            break;
        }
    }

    while (1) {
        cout << "Please enter the amount of this transaction (enter a negative number for withdrawal):" << endl;
        cin >> amount;
        if (cin.fail()) {
            cout << "That was not a valid amount." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (account.get_balance() < -amount) {
            cout << "the account does not have enough balance to complete the transaction. ";
            cout << "current balance: " << account.get_balance() << endl;
            continue;
        } else {
            cout << "You entered: " << amount << endl << endl;
            break;
        }
    }
    account.add_transaction(type, amount);
    account.change_balance(amount);
    cout << "Transation made successful! Current account balance: " << account.get_balance() << endl;
}

int main() {
    vector<Account> listofAccount;
    string input;
    int totalAccount = 0;
    cout << "Welcome! ";
    while(1) {
        cout << "Please enter your command below. Type \"help\" for more information." << endl;
        getline(cin, input);
        if (input == "create") {
            listofAccount.push_back(CreateAccount());
            totalAccount++;
            cout << "The account has been added!" << endl;
        } 
        
        else if (input == "print account summary") {
            string aName;
            string fileName;
            int AccountIndex = 0;
            int LoopControl = 1;
            while (LoopControl) {
                cout << "Please enter the account name of the account you'd like to print:" << endl;
                getline(cin, aName);
                for (; AccountIndex < totalAccount; ) {
                    if (listofAccount[AccountIndex].get_name() == aName) {
                        LoopControl = 0;
                       break;
                    }
                    AccountIndex++;
                }
                if (LoopControl) {
                    cout << "The account name you entered does not exist." << endl;
                }
            }

            cout << "Generating account summary for: " << aName << "." << endl;
            cout << "Please enter a name for the summary file:" << endl;
            getline(cin, fileName);
            listofAccount[AccountIndex].generateAccountSummary(fileName);
            cout << "The account summary has been generated as " << fileName << ".txt!" << endl << endl;
        } 

        else if (input == "transaction") {
            string aName;
            int AccountIndex = 0;
            int LoopControl = 1;
            while (LoopControl) {
                cout << "Please enter the account name you'd like to make a transaction:" << endl;
                getline(cin, aName);
                for (; AccountIndex < totalAccount; ) {
                    if (listofAccount[AccountIndex].get_name() == aName) {
                        LoopControl = 0;
                        break;
                    }
                    AccountIndex++;
                }
                if (LoopControl) {
                    cout << "The account name you entered does not exist." << endl;
                }
            }

            cout << "Making transaction for: " << aName << "." << endl;
            AddTransaction(listofAccount[AccountIndex]);
        }
        /*
        else if (input == "delete") {

        }

        else if (input == "clear transaction") {

        }
        */
        
        else if (input == "quit" || input == "q") {
            break;
        } 
        
        else {
            cout << "\"" << input << "\" is not a valid command." << endl;
            cin.clear();
        }
    }
}