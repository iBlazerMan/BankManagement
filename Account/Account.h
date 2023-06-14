#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Account {
private:
    // PIMPL class declaration
    class AccountImpl;
    AccountImpl* impl;

public:
    // constructor
    Account(const string& inp_name, double inp_balance, int inp_card_number);

    // destructor
    ~Account();

    // returns the account's current balance
    double get_balance();

    // modify the current account's balance
    void change_balance(double amount);

    // returns the account's name
    string get_name();

    // returns card number
    int get_number();

    // add a new transaction with type/amount
    void add_transaction(string type, double amount);

    // deletes all transaction records of the account
    void clear_transaction();

    // prints the transactions recorded including the type and amount to the given output stream
    void printTransaction(ostream& ostr);

    // generates a .txt file that contains all info of the account
    void generateAccountSummary(const string FileName);
};

#endif