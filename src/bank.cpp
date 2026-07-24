#include "bank.h"
#include "file_manager.h"
#include "authentication.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

Bank::Bank(const std::string& aFile, const std::string& cFile, const std::string& tFile, const std::string& auditF)
    : accountsFile(aFile), customersFile(cFile), transactionsFile(tFile), auditFile(auditF) {}

void Bank::loadData() {
    FileManager::loadAccounts(accounts, accountsFile);
    FileManager::loadCustomers(customers, customersFile);
    FileManager::loadTransactions(transactions, transactionsFile);
    std::cout << "Banking records securely loaded.\n";
    FileManager::logAudit("System Startup - Data Loaded", auditFile);
}

void Bank::saveData() const {
    FileManager::saveAccounts(accounts, accountsFile);
    FileManager::saveCustomers(customers, customersFile);
    FileManager::saveTransactions(transactions, transactionsFile);
    std::cout << "Banking records safely stored.\n";
    FileManager::logAudit("System Shutdown - Data Saved", auditFile);
}

int Bank::findAccountIndex(int accNum) const {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccountNumber() == accNum) return i;
    }
    return -1;
}

int Bank::findCustomerIndex(int custId) const {
    for (size_t i = 0; i < customers.size(); ++i) {
        if (customers[i].getId() == custId) return i;
    }
    return -1;
}

std::string Bank::generateTransactionId() const {
    int maxId = 999;
    for (const auto& tx : transactions) {
        std::string id = tx.getTransactionId();
        // Extract numeric part from "TXNxxxx" format
        if (id.length() > 3) {
            try {
                int num = std::stoi(id.substr(3));
                if (num > maxId) maxId = num;
            } catch (...) {}
        }
    }
    return "TXN" + std::to_string(maxId + 1);
}

void Bank::logTransaction(int accNum, const std::string& type, double amount) {
    std::string txId = generateTransactionId();
    std::string timeStr = Utils::getCurrentTimestamp();
    Transaction tx(txId, accNum, type, amount, timeStr);
    transactions.push_back(tx);
    
    std::string auditMsg = type + " | Acc: " + std::to_string(accNum) + " | Amt: " + std::to_string(amount);
    FileManager::logAudit(auditMsg, auditFile);
}

void Bank::createAccount() {
    std::cout << "\n--- Create New Account ---\n";
    
    std::cout << "Enter Customer ID (or 0 for new customer): ";
    int custId = Utils::getValidInt();

    if (custId == 0 || findCustomerIndex(custId) == -1) {
        if (custId != 0) {
            std::cout << "Customer not found. Creating a new profile.\n";
        }
        std::cout << "Enter New Customer ID: ";
        custId = Utils::getValidInt();
        
        while(findCustomerIndex(custId) != -1) {
            std::cout << "ID already exists. Try again: ";
            custId = Utils::getValidInt();
        }

        std::cout << "Enter Customer Name: ";
        std::string name = Utils::getValidString();
        
        std::cout << "Enter Contact Info: ";
        std::string contact = Utils::getValidString();

        customers.push_back(Customer(custId, name, contact));
    }

    std::cout << "Enter new Account Number: ";
    int accNum = Utils::getValidInt();
    while(findAccountIndex(accNum) != -1) {
        std::cout << "Account number already in use. Try again: ";
        accNum = Utils::getValidInt();
    }

    std::cout << "Select Account Type (Savings/Current): ";
    std::string type = Utils::getValidString();

    std::cout << "Enter Initial Deposit (Min 0): $";
    double initDeposit = Utils::getValidDouble();
    if (initDeposit < 0) initDeposit = 0;

    std::cout << "Set a 4-digit Secure PIN: ";
    std::string pin = Utils::getValidString();

    accounts.push_back(Account(accNum, custId, type, initDeposit, "Active", pin));
    std::cout << "Account created successfully!\n";
    
    if (initDeposit > 0) {
        logTransaction(accNum, "Initial Deposit", initDeposit);
    } else {
        FileManager::logAudit("Account Created: " + std::to_string(accNum), auditFile);
    }
}

void Bank::viewAccounts() const {
    std::cout << "\n--- All Bank Accounts ---\n";
    if (accounts.empty()) {
        std::cout << "No accounts exist.\n";
        return;
    }

    std::cout << std::left 
              << std::setw(12) << "Account#" 
              << std::setw(10) << "CustID" 
              << std::setw(15) << "Type" 
              << std::setw(15) << "Balance" 
              << "Status\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& acc : accounts) {
        acc.display();
    }
}

void Bank::depositMoney() {
    std::cout << "\n--- Deposit Money ---\n";
    std::cout << "Enter Account Number: ";
    int accNum = Utils::getValidInt();

    int idx = findAccountIndex(accNum);
    if (idx == -1) {
        std::cout << "Account not found.\n";
        return;
    }

    if (accounts[idx].getStatus() != "Active") {
        std::cout << "Account is locked or inactive.\n";
        return;
    }

    std::cout << "Enter Amount to Deposit: $";
    double amt = Utils::getValidDouble();

    if (accounts[idx].deposit(amt)) {
        std::cout << "Deposit successful! New Balance: $" << std::fixed << std::setprecision(2) << accounts[idx].getBalance() << "\n";
        logTransaction(accNum, "Deposit", amt);
    } else {
        std::cout << "Invalid deposit amount.\n";
    }
}

void Bank::withdrawMoney() {
    std::cout << "\n--- Withdraw Money ---\n";
    std::cout << "Enter Account Number: ";
    int accNum = Utils::getValidInt();

    int idx = findAccountIndex(accNum);
    if (idx == -1) {
        std::cout << "Account not found.\n";
        return;
    }

    if (accounts[idx].getStatus() != "Active") {
        std::cout << "Account is locked or inactive.\n";
        return;
    }

    if (!Authentication::validatePIN(accounts[idx].getPIN())) {
        return;
    }

    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << accounts[idx].getBalance() << "\n";
    std::cout << "Enter Amount to Withdraw: $";
    double amt = Utils::getValidDouble();

    if (accounts[idx].withdraw(amt)) {
        std::cout << "Withdrawal successful! New Balance: $" << std::fixed << std::setprecision(2) << accounts[idx].getBalance() << "\n";
        logTransaction(accNum, "Withdrawal", amt);
    } else {
        std::cout << "Withdrawal failed. Insufficient funds or invalid amount.\n";
        FileManager::logAudit("Failed Withdrawal Attempt Acc: " + std::to_string(accNum), auditFile);
    }
}

void Bank::transferFunds() {
    std::cout << "\n--- Transfer Funds ---\n";
    std::cout << "Enter Sender Account Number: ";
    int senderAcc = Utils::getValidInt();

    int sIdx = findAccountIndex(senderAcc);
    if (sIdx == -1) {
        std::cout << "Sender account not found.\n";
        return;
    }

    if (accounts[sIdx].getStatus() != "Active") {
        std::cout << "Sender account is locked or inactive.\n";
        return;
    }

    if (!Authentication::validatePIN(accounts[sIdx].getPIN())) {
        return;
    }

    std::cout << "Enter Receiver Account Number: ";
    int receiverAcc = Utils::getValidInt();

    if (senderAcc == receiverAcc) {
        std::cout << "Cannot transfer to the same account.\n";
        return;
    }

    int rIdx = findAccountIndex(receiverAcc);
    if (rIdx == -1) {
        std::cout << "Receiver account not found.\n";
        return;
    }

    if (accounts[rIdx].getStatus() != "Active") {
        std::cout << "Receiver account is locked or inactive.\n";
        return;
    }

    std::cout << "Available Balance: $" << std::fixed << std::setprecision(2) << accounts[sIdx].getBalance() << "\n";
    std::cout << "Enter Amount to Transfer: $";
    double amt = Utils::getValidDouble();

    if (accounts[sIdx].withdraw(amt)) {
        accounts[rIdx].deposit(amt);
        std::cout << "Transfer of $" << amt << " successful!\n";
        logTransaction(senderAcc, "Transfer Out", amt);
        logTransaction(receiverAcc, "Transfer In", amt);
    } else {
        std::cout << "Transfer failed. Insufficient funds or invalid amount.\n";
        FileManager::logAudit("Failed Transfer from " + std::to_string(senderAcc) + " to " + std::to_string(receiverAcc), auditFile);
    }
}

void Bank::viewTransactionHistory() const {
    std::cout << "\n--- Transaction History ---\n";
    std::cout << "Enter Account Number (or 0 for global history): ";
    int accNum = Utils::getValidInt();

    std::cout << "\n" << std::left 
              << std::setw(15) << "TXN ID" 
              << std::setw(12) << "Account#" 
              << std::setw(15) << "Type" 
              << std::setw(15) << "Amount" 
              << "Timestamp\n";
    std::cout << std::string(80, '-') << "\n";

    bool found = false;
    for (const auto& tx : transactions) {
        if (accNum == 0 || tx.getAccountNumber() == accNum) {
            tx.display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No transactions found.\n";
    }
}

void Bank::showStatistics() const {
    std::cout << "\n--- Banking Statistics Dashboard ---\n";
    
    double totalAssets = 0;
    int activeAccounts = 0;
    int lockedAccounts = 0;

    for (const auto& acc : accounts) {
        totalAssets += acc.getBalance();
        if (acc.getStatus() == "Active") activeAccounts++;
        else lockedAccounts++;
    }

    std::cout << "Total Customers: " << customers.size() << "\n";
    std::cout << "Total Accounts: " << accounts.size() << "\n";
    std::cout << "  - Active: " << activeAccounts << "\n";
    std::cout << "  - Locked: " << lockedAccounts << "\n";
    std::cout << "Total Bank Assets: $" << std::fixed << std::setprecision(2) << totalAssets << "\n";
    std::cout << "Total Transactions Processed: " << transactions.size() << "\n";
}
