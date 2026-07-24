#include "file_manager.h"
#include "utils.h"
#include <fstream>
#include <iostream>

namespace FileManager {

    void loadAccounts(std::vector<Account>& accounts, const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) return;

        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                accounts.push_back(Account::fromCSV(line));
            }
        }
        inFile.close();
    }

    void saveAccounts(const std::vector<Account>& accounts, const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) return;

        for (const auto& acc : accounts) {
            outFile << acc.toCSV() << "\n";
        }
        outFile.close();
    }

    void loadCustomers(std::vector<Customer>& customers, const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) return;

        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                customers.push_back(Customer::fromCSV(line));
            }
        }
        inFile.close();
    }

    void saveCustomers(const std::vector<Customer>& customers, const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) return;

        for (const auto& cust : customers) {
            outFile << cust.toCSV() << "\n";
        }
        outFile.close();
    }

    void loadTransactions(std::vector<Transaction>& transactions, const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) return;

        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                transactions.push_back(Transaction::fromCSV(line));
            }
        }
        inFile.close();
    }

    void saveTransactions(const std::vector<Transaction>& transactions, const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) return;

        for (const auto& tx : transactions) {
            outFile << tx.toCSV() << "\n";
        }
        outFile.close();
    }

    void logAudit(const std::string& message, const std::string& filename) {
        std::ofstream outFile(filename, std::ios::app);
        if (outFile.is_open()) {
            outFile << "[" << Utils::getCurrentTimestamp() << "] " << message << "\n";
            outFile.close();
        }
    }

}
