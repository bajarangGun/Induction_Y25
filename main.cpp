#include <iostream>
#include "Utils.h"
#include "Account.h"
#include "FinancialProducts.h"
#include "Customer.h"
#include "Organization.h"

using namespace std;

int main() {
    cout << "--- Final System Test: Organizational Hierarchy ---\n\n";

    // 1. Initialize the Root Bank
    Bank myBank(1, "Global Standard Bank");

    // 2. Setup Branches
    Branch* mainBranch = new Branch(101, "Downtown Main", "GSB0001", "123 Financial District");
    Branch* suburbanBranch = new Branch(102, "Uptown Suburban", "GSB0002", "456 Quiet Avenue");

    myBank.addBranch(mainBranch);
    myBank.addBranch(suburbanBranch);

    // 3. Hire Employees
    Employee* emp1 = new Employee(5001, "John Doe", "Branch Manager", 8500.0);
    Employee* emp2 = new Employee(5002, "Jane Smith", "Senior Cashier", 4500.0);
    
    mainBranch->addEmployee(emp1);
    suburbanBranch->addEmployee(emp2);

    // 4. Register a Customer (Using a masked national ID for safety)
    Customer* alice = new Customer(8801, "Alice Smith", "+1-555-0198", "alice@email.com", "XXXX-XXXX-9012");
    myBank.addCustomer(alice);

    // 5. Open an Account for the Customer at a specific Branch
    Account* aliceSavings = AccountFactory::createAccount(1, 1001, 3500.0);
    
    alice->addAccount(aliceSavings);
    mainBranch->addAccount(aliceSavings); 

    // 6. Display the Bank's Top-Level Overview
    myBank.displayBankOverview();

    // Cleanup (In a real system, you'd use smart pointers like std::unique_ptr to handle this automatically)
    delete mainBranch;
    delete suburbanBranch;
    delete emp1;
    delete emp2;
    delete alice;
    delete aliceSavings;

    return 0;
}
