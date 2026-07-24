#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "account.h"
#include "customer.h"
#include "transaction.h"
#include <vector>
#include <string>

namespace FileManager {
    void loadAccounts(std::vector<Account>& accounts, const std::string& filename);
    void saveAccounts(const std::vector<Account>& accounts, const std::string& filename);

    void loadCustomers(std::vector<Customer>& customers, const std::string& filename);
    void saveCustomers(const std::vector<Customer>& customers, const std::string& filename);

    void loadTransactions(std::vector<Transaction>& transactions, const std::string& filename);
    void saveTransactions(const std::vector<Transaction>& transactions, const std::string& filename);

    void logAudit(const std::string& message, const std::string& filename);
}

#endif // FILE_MANAGER_H
