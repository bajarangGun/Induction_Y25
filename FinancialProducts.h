#pragma once
#include <iostream>
#include <string>
#include "Account.h"
#include "Utils.h"

using namespace std;

class Transaction {
private:
    int transactionId;
    string transactionType; 
    double amount;
    string date;
    Account* sender;
    Account* receiver;
    string status;

public:
    Transaction(int id, string type, double amt, string dt, Account* sndr = nullptr, Account* rcvr = nullptr)
        : transactionId(id), transactionType(type), amount(amt), date(dt), sender(sndr), receiver(rcvr), status("Pending") {}

    void executeTransfer() {
        try {
            if (transactionType == "Transfer" && sender != nullptr && receiver != nullptr) {
                sender->withdraw(amount); 
                receiver->deposit(amount);
                status = "Success";
                cout << "[Transaction " << transactionId << "]: Transfer successful.\n";
            }
        } catch (const exception& e) {
            status = "Failed";
            cout << "[Transaction " << transactionId << "]: Transfer Failed - " << e.what() << "\n";
        }
    }
};

class ATMCard {
private:
    long cardNumber;
    int PIN;
    string cardStatus;
    Account* linkedAccount;

public:
    ATMCard(long cardNum, int pin, Account* acc)
        : cardNumber(cardNum), PIN(pin), cardStatus("Active"), linkedAccount(acc) {}

    void authenticateAndWithdraw(int inputPIN, double amount) {
        try {
            if (cardStatus == "Blocked") throw AccountBlockedException();
            if (inputPIN != PIN) throw InvalidPINException();
            linkedAccount->withdraw(amount);
        } catch (const exception& e) {
            cout << "[ATM] " << e.what() << "\n";
        }
    }
};

class Loan {
private:
    int loanId;
    string loanType;
    double principalAmount;
    string loanStatus;

public:
    Loan(int id, string type, double principal)
        : loanId(id), loanType(type), principalAmount(principal), loanStatus("Pending") {}

    void applyForLoan() {
        try {
            if (principalAmount > 500000.0) {
                loanStatus = "Rejected";
                throw runtime_error("Error: Loan amount exceeds limits.");
            }
            loanStatus = "Approved";
        } catch (const exception& e) {
            cout << "Loan Denied: " << e.what() << "\n";
        }
    }

    // NEW METHOD ADDED HERE
    void displayLoanDetails() const {
        cout << "[Loan ID: " << loanId << "] Type: " << loanType 
             << " | Principal: $" << principalAmount << " | Status: " << loanStatus << "\n";
    }
};
