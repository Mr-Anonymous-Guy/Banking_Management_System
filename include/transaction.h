#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string transactionId;
    int accountNumber;
    std::string type; // Deposit, Withdrawal, Transfer In, Transfer Out
    double amount;
    std::string timestamp;

public:
    Transaction() : accountNumber(0), amount(0.0) {}
    Transaction(const std::string& txId, int accNum, const std::string& type, double amount, const std::string& time);

    int getAccountNumber() const;
    std::string getTransactionId() const;
    
    void display() const;

    std::string toCSV() const;
    static Transaction fromCSV(const std::string& csvLine);
};

#endif // TRANSACTION_H
