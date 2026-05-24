#pragma once
#include <iostream>
#include <string>
#include "Utils.h"

using namespace std;

// Abstract Base Class
class Account {
protected:
    long accountNumber;
    string accountType;
    double balance;
    string status; 
public:
    Account(long accNum, string type, double bal) 
        : accountNumber(accNum), accountType(type), balance(bal), status("Active") {}
    
    virtual ~Account() = default;
    
    virtual void deposit(double amount) {
        if(status == "Blocked") throw AccountBlockedException();
        balance += amount;
        cout << "Deposited $" << amount << " into Account " << accountNumber << ".\n";
    }
    
    // Pure virtual functions
    virtual void withdraw(double amount) = 0;
    virtual void displayAccountInfo() const = 0;

    double getBalance() const { return balance; }
    long getAccountNumber() const { return accountNumber; }
};

// Derived: Savings Account
class SavingsAccount : public Account {
private:
    double interestRate;
    double minimumBalance;
public:
    SavingsAccount(long accNum, double bal, double rate, double minBal)
        : Account(accNum, "Savings", bal), interestRate(rate), minimumBalance(minBal) {}

    void withdraw(double amount) override {
        if(status == "Blocked") throw AccountBlockedException();
        if (balance - amount < minimumBalance) throw InsufficientBalanceException();
        
        balance -= amount;
        cout << "Withdrew $" << amount << ". Remaining Balance: $" << balance << "\n";
    }

    void displayAccountInfo() const override {
        cout << "[Savings Account] ID: " << accountNumber << " | Balance: $" << balance 
             << " | Interest Rate: " << interestRate << "%\n";
    }
};

// Derived: Current Account
class CurrentAccount : public Account {
private:
    double overdraftLimit;
    string businessName;
public:
    CurrentAccount(long accNum, double bal, double overdraft, string bizName)
        : Account(accNum, "Current", bal), overdraftLimit(overdraft), businessName(bizName) {}

    void withdraw(double amount) override {
        if(status == "Blocked") throw AccountBlockedException();
        if (balance + overdraftLimit < amount) throw InsufficientBalanceException();
        
        balance -= amount;
        cout << "Withdrew $" << amount << ". Remaining Balance: $" << balance << "\n";
    }

    void displayAccountInfo() const override {
        cout << "[Current Account] ID: " << accountNumber << " | Business: " << businessName 
             << " | Balance: $" << balance << " | Overdraft Limit: $" << overdraftLimit << "\n";
    }
};

// Factory Pattern for Account Creation
class AccountFactory {
public:
    static Account* createAccount(int typeCode, long accNum, double initBal, string extraStr = "") {
        switch(typeCode) {
            case 1: return new SavingsAccount(accNum, initBal, 4.0, 500.0);
            case 2: return new CurrentAccount(accNum, initBal, 5000.0, extraStr);
            default: return nullptr;
        }
    }
};
