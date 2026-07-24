#ifndef BANK_H
#define BANK_H

#include "account.h"
#include "customer.h"
#include "transaction.h"
#include <vector>
#include <string>

class Bank {
private:
    std::vector<Account> accounts;
    std::vector<Customer> customers;
    std::vector<Transaction> transactions;

    std::string accountsFile;
    std::string customersFile;
    std::string transactionsFile;
    std::string auditFile;

    int findAccountIndex(int accNum) const;
    int findCustomerIndex(int custId) const;

    std::string generateTransactionId() const;
    void logTransaction(int accNum, const std::string& type, double amount);

public:
    Bank(const std::string& aFile, const std::string& cFile, const std::string& tFile, const std::string& auditF);

    void loadData();
    void saveData() const;

    void createAccount();
    void viewAccounts() const;
    
    void depositMoney();
    void withdrawMoney();
    void transferFunds();
    
    void viewTransactionHistory() const;
    void showStatistics() const;
};

#endif // BANK_H
