cmake_minimum_required (VERSION 3.26.3)
project (BankManagement)
include_directories(Account)
add_executable (BankManagement Bank_Management.cpp ./Account/Account.cpp)
