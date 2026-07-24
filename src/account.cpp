#include "account.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Account::Account(int accNum, int custId, const std::string& type, double balance, const std::string& status, const std::string& pin)
    : accountNumber(accNum), customerId(custId), type(type), balance(balance), status(status), pin(pin) {}

int Account::getAccountNumber() const { return accountNumber; }
int Account::getCustomerId() const { return customerId; }
std::string Account::getType() const { return type; }
double Account::getBalance() const { return balance; }
std::string Account::getStatus() const { return status; }
std::string Account::getPIN() const { return pin; }

void Account::setStatus(const std::string& newStatus) {
    status = newStatus;
}

bool Account::deposit(double amount) {
    if (amount <= 0) return false;
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0) return false;
    if (balance < amount) return false; // Overdraft protection
    balance -= amount;
    return true;
}

void Account::display() const {
    std::cout << std::left 
              << std::setw(12) << accountNumber 
              << std::setw(10) << customerId 
              << std::setw(15) << type 
              << "$" << std::setw(14) << std::fixed << std::setprecision(2) << balance 
              << status << "\n";
}

std::string Account::toCSV() const {
    std::stringstream ss;
    ss << accountNumber << "," << customerId << "," << type << "," << std::fixed << std::setprecision(2) << balance << "," << status << "," << pin;
    return ss.str();
}

Account Account::fromCSV(const std::string& csvLine) {
    Account acc;
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ',')) acc.accountNumber = std::stoi(token);
    if (std::getline(ss, token, ',')) acc.customerId = std::stoi(token);
    if (std::getline(ss, token, ',')) acc.type = token;
    if (std::getline(ss, token, ',')) acc.balance = std::stod(token);
    if (std::getline(ss, token, ',')) acc.status = token;
    if (std::getline(ss, token, ',')) acc.pin = token;

    return acc;
}
