#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Account.h"
#include "FinancialProducts.h"

using namespace std;

class Customer {
private:
    int customerId;
    string fullName;
    string mobileNumber;
    string email;
    string aadhaarNumber; // National ID
    
    // Aggregation: A customer "has-a" list of accounts and loans
    vector<Account*> accounts;
    vector<Loan*> loans;

public:
    Customer(int id, string name, string mobile, string mail, string aadhaar)
        : customerId(id), fullName(name), mobileNumber(mobile), email(mail), aadhaarNumber(aadhaar) {}

    // Method to link an existing account to this customer
    void addAccount(Account* acc) {
        accounts.push_back(acc);
    }

    // Method to link an existing loan to this customer
    void addLoan(Loan* loan) {
        loans.push_back(loan);
    }

    // Display a comprehensive portfolio for the customer
    void displayCustomerProfile() const {
        cout << "\n=========================================\n";
        cout << "   CUSTOMER PORTFOLIO: " << fullName << "\n";
        cout << "=========================================\n";
        cout << "Customer ID : " << customerId << "\n";
        cout << "Contact     : " << mobileNumber << " | " << email << "\n";
        cout << "Aadhaar No  : " << aadhaarNumber << "\n";
        
        cout << "\n--- Linked Accounts (" << accounts.size() << ") ---\n";
        if (accounts.empty()) {
            cout << "No active accounts.\n";
        } else {
            for (const auto& acc : accounts) {
                acc->displayAccountInfo();
            }
        }

        cout << "\n--- Linked Loans (" << loans.size() << ") ---\n";
        if (loans.empty()) {
            cout << "No active loans.\n";
        } else {
            for (const auto& loan : loans) {
                loan->displayLoanDetails();
            }
        }
        cout << "=========================================\n\n";
    }
};
