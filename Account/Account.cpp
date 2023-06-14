#include "Account.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Account::AccountImpl {
    std::string* name;
    double balance;
    int card_number;
    std::string** transaction_type;
    double* transaction_amount;
};

Account::Account(const string& inp_name, double inp_balance, int inp_card_number) {
    impl = new AccountImpl;
    impl->name = new string(inp_name);
    impl->balance = inp_balance;
    impl->card_number = inp_card_number;
    impl->transaction_amount = new double[20];
    impl->transaction_type = new string*[20];
    for (int i = 0; i < 20; ++i) {
        impl->transaction_type[i] = new string;
        impl->transaction_amount[i] = 0;
    }
}

Account::~Account() {
    delete impl->name;
    for (int i = 0; i < 20; ++i) {
        delete impl->transaction_type[i];
    }
    delete[] impl->transaction_type;
    delete[] impl->transaction_amount;
    delete impl;
}

double Account::get_balance() {
    return impl->balance;
}

void Account::change_balance(double amount) {
    impl->balance += amount;
}

string Account::get_name() {
    return *(impl->name);
}

int Account::get_number() {
    return impl->card_number;
}

void Account::add_transaction(string type, double amount) {
    bool first = true;
    for (int i = 18; i >= 0; --i) {
        if (impl->transaction_amount[i] != 0) {
            if (first) {
                delete impl->transaction_type[i + 1];
                first = false;
            }
            impl->transaction_amount[i + 1] = impl->transaction_amount[i]; 
            impl->transaction_type[i + 1] = impl->transaction_type[i];
        }
    }
    impl->transaction_amount[0] = amount;
    impl->transaction_type[0] = new string(type);
}

void Account::clear_transaction() {
    for (int i = 0; i < 20; ++i) {
        delete impl->transaction_type[i];
        impl->transaction_type[i] = new string;
        impl->transaction_amount[i] = 0;
    }
}

void Account::printTransaction(ostream& ostr) {
    if (impl->transaction_amount[0] == 0) {
        ostr << "There are no transaction on record." << "\n" << endl;
        return;
    }
    int i = 0;
    ostr << "Most recent transactions:" << endl;
    while (impl->transaction_amount[i] != 0) { 
        ostr << "Transaction #" << (i + 1) << endl;
        ostr << "Transaction type: " << *impl->transaction_type[i] << endl;
        if (impl->transaction_amount[i] > 0) {
            ostr << "Balance change: +" << impl->transaction_amount[i];
        } else {
            ostr << "Balance change: " << impl->transaction_amount[i];
        }
        ostr << "\n" << endl;
        i++;
    }
}

void Account::generateAccountSummary(const string FileName) {
    string generatedFileName = FileName + ".txt";
    ofstream summary(generatedFileName);
    summary << "Name: " << get_name() << endl;
    summary << "Card Number: " << get_number() << endl;
    summary << "Current Balance: " << get_balance() << "\n" << endl;
    printTransaction(summary);
    summary.close();
}
