#include <iostream>
#include "bank.h"
#include "utils.h"

void displayMenu() {
    std::cout << "\n========================================\n";
    std::cout << "       BANKING MANAGEMENT SYSTEM        \n";
    std::cout << "========================================\n";
    std::cout << "1. Create Account\n";
    std::cout << "2. View Accounts\n";
    std::cout << "3. Deposit Money\n";
    std::cout << "4. Withdraw Money\n";
    std::cout << "5. Transfer Funds\n";
    std::cout << "6. Transaction History\n";
    std::cout << "7. Statistics Dashboard\n";
    std::cout << "8. Save & Exit\n";
    std::cout << "========================================\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Bank bank("data/accounts.txt", "data/customers.txt", "data/transactions.txt", "data/audit_logs.txt");
    bank.loadData();

    bool isRunning = true;

    while (isRunning) {
        displayMenu();
        int choice = Utils::getValidInt();

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.viewAccounts();
                break;
            case 3:
                bank.depositMoney();
                break;
            case 4:
                bank.withdrawMoney();
                break;
            case 5:
                bank.transferFunds();
                break;
            case 6:
                bank.viewTransactionHistory();
                break;
            case 7:
                bank.showStatistics();
                break;
            case 8:
                std::cout << "Saving records and initiating shutdown sequence...\n";
                bank.saveData();
                std::cout << "\nThank you for using the Banking Management System. Secure exit complete.\n";
                isRunning = false;
                break;
            default:
                std::cout << "Invalid choice. Please select a number between 1 and 8.\n";
                break;
        }
    }

    return 0;
}
