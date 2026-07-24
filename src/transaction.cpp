#include "transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Transaction::Transaction(const std::string& txId, int accNum, const std::string& type, double amount, const std::string& time)
    : transactionId(txId), accountNumber(accNum), type(type), amount(amount), timestamp(time) {}

int Transaction::getAccountNumber() const {
    return accountNumber;
}

std::string Transaction::getTransactionId() const {
    return transactionId;
}

void Transaction::display() const {
    std::cout << std::left 
              << std::setw(15) << transactionId 
              << std::setw(12) << accountNumber 
              << std::setw(15) << type 
              << "$" << std::setw(14) << std::fixed << std::setprecision(2) << amount 
              << timestamp << "\n";
}

std::string Transaction::toCSV() const {
    std::stringstream ss;
    ss << transactionId << "," << accountNumber << "," << type << "," << amount << "," << timestamp;
    return ss.str();
}

Transaction Transaction::fromCSV(const std::string& csvLine) {
    Transaction tx;
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ',')) tx.transactionId = token;
    if (std::getline(ss, token, ',')) tx.accountNumber = std::stoi(token);
    if (std::getline(ss, token, ',')) tx.type = token;
    if (std::getline(ss, token, ',')) tx.amount = std::stod(token);
    if (std::getline(ss, token, ',')) tx.timestamp = token;

    return tx;
}
