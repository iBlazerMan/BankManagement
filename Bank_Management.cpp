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
    string transaction_type[10];
    int transaction_amount[10];

public:
    // constructor
    Account(const string& inp_name, double inp_balance, int inp_card_number) {
        name = inp_name;
        balance = inp_balance;
        card_number = inp_card_number;
        for (int i = 0; i < 10; ++i) {
            transaction_type[i] = "";
            transaction_amount[i] = 0;
        }
    }

    // returns the account's balance
    double get_balance() {
        return balance;
    }

    // returns the account's name
    string get_name() {
        return name;
    }

    // returns card number
    int get_number() {
        return card_number;
    }

    // prints the transactions recorded including the type and amount to the given output stream
    void printTransaction(ostream& ostr) {
        int i = 0;
        ostr << "Most recent transactions:" << endl;
        while (transaction_amount[i] != 0) { 
            ostr << "Transaction #" << i << endl;
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

int main() {
    vector<Account> listofAccount;
    string input;
    int totalAccount = 0;
    cout << "Welcome! ";
    while(1) {
        cout << "Please enter your command below. Type \"help\" for more information." << endl;
        getline(cin, input);
        if (input == "create") {
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
                    cout << "You entered: " << aName << endl << endl;
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
                if (!cin.fail()) {
                    cout << "You entered: " << aBalance << endl << endl;
                    break;
                } else {
                    cout << "That was not a valid balance number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            listofAccount.push_back(Account(aName, aBalance, aNumber));
            totalAccount++;
            cout << "The account has been added!" << endl << endl;
        } 
        
        else if (input == "print Account") {
            string aName;
            string fileName;

            // add invalid input protection

            cout << "Please enter the account name of the account you'd like to print:" << endl;
            getline(cin, aName);
            cout << "Please enter the name of the summary file:" << endl;
            getline(cin, fileName);
            for (int i = 0; i < totalAccount; ++i) {
                if (listofAccount[i].get_name() == aName) {
                    listofAccount[i].generateAccountSummary(fileName);
                    break;
                }
            }
            cout << "The account summary has been generated as " << fileName << ".txt!" << endl << endl;
        } 
        
        else if (input == "quit" || input == "q") {
            break;
        } 
        
        else {
            cout << "That was not a valid command." << endl;
            cin.clear();
        }
    }
}