#pragma once
#include <iostream>
#include <string>
#include <exception>

using namespace std;

// --- Exceptions ---
class InsufficientBalanceException : public exception {
    public: const char* what() const noexcept override { return "Error: Insufficient balance."; }
};
class InvalidPINException : public exception {
    public: const char* what() const noexcept override { return "Error: Invalid ATM PIN."; }
};
class AccountBlockedException : public exception {
    public: const char* what() const noexcept override { return "Error: Account is blocked."; }
};

// --- Notification Strategy Pattern ---
class Notification {
protected:
    string message;
public:
    Notification(string msg) : message(msg) {}
    virtual void sendNotification() = 0;
    virtual ~Notification() = default;
};

class SMSNotification : public Notification {
private:
    string phoneNumber;
public:
    SMSNotification(string phone, string msg) : Notification(msg), phoneNumber(phone) {}
    void sendNotification() override {
        cout << "[SMS to " << phoneNumber << "]: " << message << " | Status: Sent\n";
    }
};

class EmailNotification : public Notification {
private:
    string emailAddress;
public:
    EmailNotification(string email, string msg) : Notification(msg), emailAddress(email) {}
    void sendNotification() override {
        cout << "[Email to " << emailAddress << "]:\n" << message << "\nStatus: Sent\n";
    }
};
