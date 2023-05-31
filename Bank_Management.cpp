#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "Account.h"
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
  Account(const string inp_name, int inp_balance, int inp_card_number) {
    name = inp_name;
    balance = inp_balance;
    card_number = inp_card_number;
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

}




