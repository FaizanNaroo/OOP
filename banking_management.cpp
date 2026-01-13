#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

// ANSI color codes for console output
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";

class Account {
protected:
    double balance; // Changed to double for precise calculations
public:
    Account() : balance(0.0) {}

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << GREEN << "Deposited $" << fixed << setprecision(2) << amount 
                 << " to account. New balance: $" << balance << RESET << endl;
        } else {
            cout << RED << "Invalid deposit amount! Must be positive." << RESET << endl;
        }
    }

    virtual bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << GREEN << "Withdrew $" << fixed << setprecision(2) << amount 
                 << " from account. New balance: $" << balance << RESET << endl;
            return true;
        } else {
            cout << RED << "Invalid withdrawal! Insufficient funds or negative amount." << RESET << endl;
            return false;
        }
    }

    virtual double getBalance() const {
        return balance;
    }

    virtual ~Account() = default;
};

class CheckingAccount : public Account {
public:
    void deposit(double amount) override {
        Account::deposit(amount);
    }

    bool withdraw(double amount) override {
        return Account::withdraw(amount);
    }
};

class SavingAccount : public Account {
private:
    const double interestRate = 0.05; // 5% annual interest
public:
    void deposit(double amount) override {
        Account::deposit(amount);
    }

    bool withdraw(double amount) override {
        if (amount > 0 && balance >= amount + 5.0) { // $5 withdrawal fee
            balance -= 5.0; // Apply fee
            cout << YELLOW << "Applied $5.00 withdrawal fee to savings." << RESET << endl;
            return Account::withdraw(amount);
        } else {
            cout << RED << "Invalid withdrawal! Insufficient funds (including $5 fee) or negative amount." << RESET << endl;
            return false;
        }
    }

    void calculateInterest() {
        if (balance > 0) {
            double interest = balance * interestRate;
            balance += interest;
            cout << GREEN << "Applied interest: $" << fixed << setprecision(2) << interest 
                 << ". New savings balance: $" << balance << RESET << endl;
        }
    }
};

class Transaction {
public:
    string type;
    double amount;
    string account;
    double newBalance;

    Transaction(const string& t, double amt, const string& acc, double bal) 
        : type(t), amount(amt), account(acc), newBalance(bal) {}
};

class BankCustomer {
private:
    CheckingAccount checking;
    SavingAccount savings;
    vector<Transaction> transactionHistory;

    void logTransaction(const string& type, double amount, const string& account, double newBalance) {
        transactionHistory.emplace_back(type, amount, account, newBalance);
    }

public:
    void deposit(double amount) {
        if (amount > 0) {
            double half = amount / 2.0;
            checking.deposit(half);
            savings.deposit(amount - half); // Ensure exact split
            logTransaction("Deposit", half, "Checking", checking.getBalance());
            logTransaction("Deposit", amount - half, "Savings", savings.getBalance());
        } else {
            cout << RED << "Invalid deposit amount! Must be positive." << RESET << endl;
        }
    }

    void withdraw(double amount, const string& accountType) {
        bool success = false;
        if (accountType == "checking") {
            success = checking.withdraw(amount);
            if (success) {
                logTransaction("Withdrawal", amount, "Checking", checking.getBalance());
            }
        } else if (accountType == "savings") {
            success = savings.withdraw(amount);
            if (success) {
                logTransaction("Withdrawal", amount, "Savings", savings.getBalance());
            }
        } else {
            cout << RED << "Invalid account type! Use 'checking' or 'savings'." << RESET << endl;
        }
    }

    void applyInterestToSavings() {
        savings.calculateInterest();
        logTransaction("Interest", savings.getBalance() * 0.05, "Savings", savings.getBalance());
    }

    void showBalances() const {
        cout << GREEN << "Checking Balance: $" << fixed << setprecision(2) << checking.getBalance() << RESET << endl;
        cout << GREEN << "Savings Balance: $" << fixed << setprecision(2) << savings.getBalance() << RESET << endl;
    }

    void showTransactionHistory() const {
        cout << YELLOW << "\nTransaction History:\n" << RESET;
        if (transactionHistory.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        cout << left << setw(15) << "Type" << setw(15) << "Amount" << setw(15) << "Account" << setw(15) << "New Balance" << endl;
        cout << string(60, '-') << endl;
        for (const auto& t : transactionHistory) {
            cout << left << setw(15) << t.type << "$" << fixed << setprecision(2) << setw(14) << t.amount 
                 << setw(15) << t.account << "$" << setw(14) << t.newBalance << endl;
        }
    }

    void displayWelcome() const {
        cout << YELLOW << R"(
        ==============================
           Welcome to xAI Bank!
        ==============================
        )" << RESET << endl;
        cout << "Instructions:\n";
        cout << "  - Deposits are split evenly between checking and savings accounts.\n";
        cout << "  - Withdrawals from savings incur a $5 fee.\n";
        cout << "  - Savings earn 5% interest when 'applyinterest' is used.\n";
        cout << "  - All amounts must be positive and withdrawals must not exceed account balance.\n";
        cout << "Commands:\n";
        cout << "  deposit <amount>         - Deposit amount to both accounts\n";
        cout << "  withdraw <amount> <type> - Withdraw from checking or savings\n";
        cout << "  applyinterest           - Apply 5% interest to savings\n";
        cout << "  balance                 - Show account balances\n";
        cout << "  history                 - Show transaction history\n";
        cout << "  quit                    - Exit the program\n";
    }
};

void runBankSystem() {
    BankCustomer customer;
    customer.displayWelcome();

    while (true) {
        cout << "\nEnter command: ";
        string command;
        cin >> command;

        if (command == "deposit") {
            double amount;
            if (cin >> amount) {
                customer.deposit(amount);
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "Invalid amount!" << RESET << endl;
            }
        } else if (command == "withdraw") {
            double amount;
            string accountType;
            if (cin >> amount >> accountType) {
                customer.withdraw(amount, accountType);
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "Invalid amount or account type!" << RESET << endl;
            }
        } else if (command == "applyinterest") {
            customer.applyInterestToSavings();
        } else if (command == "balance") {
            customer.showBalances();
        } else if (command == "history") {
            customer.showTransactionHistory();
        } else if (command == "quit") {
            cout << YELLOW << "\nThank you for banking with xAI Bank!" << RESET << endl;
            break;
        } else {
            cout << RED << "Unknown command! Available: deposit, withdraw, applyinterest, balance, history, quit" << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    runBankSystem();
    return 0;
}