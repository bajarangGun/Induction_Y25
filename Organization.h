#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Customer.h"
#include "Account.h"

using namespace std;

class Branch; // Forward declaration to allow Employee to reference it

// --- Employee Class ---
class Employee {
private:
    int employeeId;
    string employeeName;
    string designation;
    double salary;
    Branch* branch;

public:
    Employee(int id, string name, string desig, double sal)
        : employeeId(id), employeeName(name), designation(desig), salary(sal), branch(nullptr) {}

    void assignBranch(Branch* b) {
        branch = b;
    }

    void displayEmployee() const {
        cout << "[Employee ID: " << employeeId << "] " << employeeName 
             << " | Role: " << designation << " | Salary: $" << salary << "\n";
    }
};

// --- Branch Class ---
class Branch {
private:
    int branchId;
    string branchName;
    string IFSCCode;
    string address;
    
    // Aggregation: A branch manages multiple accounts and employees
    vector<Account*> accounts;
    vector<Employee*> employees;

public:
    Branch(int id, string name, string ifsc, string addr)
        : branchId(id), branchName(name), IFSCCode(ifsc), address(addr) {}

    void addEmployee(Employee* emp) {
        employees.push_back(emp);
        emp->assignBranch(this); // Bidirectional link
    }

    void addAccount(Account* acc) {
        accounts.push_back(acc);
    }

    void displayBranchDetails() const {
        cout << "\n=== Branch: " << branchName << " (" << IFSCCode << ") ===\n";
        cout << "Address: " << address << "\n";
        cout << "Total Employees: " << employees.size() << "\n";
        cout << "Total Accounts: " << accounts.size() << "\n";
        for (const auto& emp : employees) {
            emp->displayEmployee();
        }
    }
};

// --- Bank Class (Root Entity) ---
class Bank {
private:
    int bankId;
    string bankName;
    
    // Composition/Aggregation: The bank owns the branches and manages the customers
    vector<Branch*> branches;
    vector<Customer*> customers;

public:
    Bank(int id, string name) : bankId(id), bankName(name) {}

    void addBranch(Branch* b) {
        branches.push_back(b);
    }

    void addCustomer(Customer* c) {
        customers.push_back(c);
    }

    void displayBankOverview() const {
        cout << "\n*****************************************\n";
        cout << "   BANK OVERVIEW: " << bankName << "\n";
        cout << "*****************************************\n";
        cout << "Total Branches : " << branches.size() << "\n";
        cout << "Total Customers: " << customers.size() << "\n";
        
        for (const auto& b : branches) {
            b->displayBranchDetails();
        }
        cout << "*****************************************\n\n";
    }
};
