#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    int accountNumber;
    int customerId;
    std::string type; // Savings, Current
    double balance;
    std::string status; // Active, Locked
    std::string pin;

public:
    Account() : accountNumber(0), customerId(0), balance(0.0) {}
    Account(int accNum, int custId, const std::string& type, double balance, const std::string& status, const std::string& pin);

    int getAccountNumber() const;
    int getCustomerId() const;
    std::string getType() const;
    double getBalance() const;
    std::string getStatus() const;
    std::string getPIN() const;

    void setStatus(const std::string& newStatus);
    bool deposit(double amount);
    bool withdraw(double amount);

    void display() const;

    std::string toCSV() const;
    static Account fromCSV(const std::string& csvLine);
};

#endif // ACCOUNT_H
