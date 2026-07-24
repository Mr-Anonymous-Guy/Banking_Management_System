# Banking Management System

An advanced C++ banking application built with Object-Oriented Principles. Simulates a real-world bank with secure PIN authentication, fund transfers with overdraft protection, comprehensive transaction history, and full audit logging.

## Features

- **Account Management**: Create Savings/Current accounts linked to customer profiles.
- **Deposits & Withdrawals**: Safe financial operations with overdraft protection and positive-amount validation.
- **Fund Transfers**: Transfer between accounts with sender/receiver validation and self-transfer prevention.
- **PIN Authentication**: 3-attempt lockout system for withdrawal and transfer operations.
- **Transaction History**: View transaction logs per account or globally with timestamps.
- **Statistics Dashboard**: Total customers, accounts (active/locked), bank assets, and transaction count.
- **Audit Logging**: Dedicated audit trail (`audit_logs.txt`) for full system traceability.
- **Collision-Safe IDs**: Transaction IDs increment from the highest existing ID, preventing duplicates across sessions.

## Folder Structure

```text
Banking_Management_System/
├── README.md
├── LICENSE
├── .gitignore
├── Makefile
├── run.sh
├── src/
│   ├── main.cpp
│   ├── bank.cpp
│   ├── account.cpp
│   ├── customer.cpp
│   ├── transaction.cpp
│   ├── authentication.cpp
│   ├── file_manager.cpp
│   └── utils.cpp
├── include/
│   ├── bank.h
│   ├── account.h
│   ├── customer.h
│   ├── transaction.h
│   ├── authentication.h
│   ├── file_manager.h
│   └── utils.h
├── data/                 # Runtime data (accounts, customers, transactions, audit logs)
└── build/                # Compiled output
```

## Build & Run

```bash
# Build
make

# Run
make run

# Or use the helper script
./run.sh

# Clean compiled files
make clean
```

### Windows

```cmd
build.bat
run.bat
clean.bat
```

## Sample Output

```text
========================================
       BANKING MANAGEMENT SYSTEM
========================================
1. Create Account
2. View Accounts
3. Deposit Money
4. Withdraw Money
5. Transfer Funds
6. Transaction History
7. Statistics Dashboard
8. Save & Exit
========================================

--- All Bank Accounts ---
Account#    CustID    Type           Balance        Status
------------------------------------------------------------
1001        1         Savings        $5,250.00      Active
1002        2         Current        $12,800.50     Active

--- Banking Statistics Dashboard ---
Total Customers: 2
Total Accounts: 2
  - Active: 2
  - Locked: 0
Total Bank Assets: $18,050.50
Total Transactions Processed: 7
```

## Architecture

```text
┌─────────┐     ┌──────────┐     ┌─────────────┐
│  main   │────▶│   Bank   │────▶│ FileManager │──▶ data/*.txt
└─────────┘     └──────────┘     └─────────────┘
                     │
          ┌──────────┼──────────┐
          ▼          ▼          ▼
     ┌─────────┐ ┌──────────┐ ┌────────────────┐
     │ Account │ │ Customer │ │  Transaction   │
     └─────────┘ └──────────┘ └────────────────┘
                                      │
                              ┌───────┴───────┐
                              │Authentication │
                              └───────────────┘
```

## Concepts Practiced

- Multi-class OOP architecture with clear separation of concerns
- Financial logic (overdraft protection, atomic transfers)
- Security patterns (PIN-based authentication with attempt limiting)
- Audit trail design (append-only logging)
- CSV-based data persistence with serialization/deserialization
- Collision-safe unique ID generation

## Future Improvements

- Encrypt stored PINs using hashing algorithms.
- Multi-threading support for concurrent ATM simulations.
- SQL database integration in place of local `.txt` storage.

## Author

Built by [Mr. Anonymous](https://github.com/Mr-Anonymous-Guy)

## License

MIT License — see [LICENSE](LICENSE) for details.
