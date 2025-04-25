#include <iostream>
#include <map>
#include <string>

// Represents an individual bank account
class Account {
public:
    std::string accountNumber;
    std::string userName;
    std::string password;
    double balance;

    // Constructor with all required fields
    Account(std::string accNum, std::string name, std::string pwd, double initialBalance)
        : accountNumber(accNum), userName(name), password(pwd), balance(initialBalance) {}
};

// Manages all banking operations and accounts
class Bank {
private:
    std::map<std::string, Account> accounts; // Key: account number, Value: Account object
    int nextAccountNumber;                   // Generates unique account numbers

public:
    Bank() : nextAccountNumber(1) {}

    // Creates a new account and returns its account number
    std::string createAccount(std::string name, std::string password, double initialDeposit) {
        std::string accNum = "ACC" + std::to_string(nextAccountNumber++);
        Account newAccount(accNum, name, password, initialDeposit);
        accounts.insert({accNum, newAccount}); // Insert new account
        std::cout << "Account created with number: " << accNum << std::endl;
        return accNum;
    }

    // Verifies login credentials
    bool verifyLogin(const std::string& accountNumber, const std::string& password) {
        auto it = accounts.find(accountNumber);
        return (it != accounts.end() && it->second.password == password);
    }

    // Deposits money into an account
    void deposit(const std::string& accountNumber, double amount) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            it->second.balance += amount;
            std::cout << "Deposited " << amount << " to account " << accountNumber << std::endl;
        } else {
            std::cout << "Account not found.\n";
        }
    }

    // Withdraws money from an account
    void withdraw(const std::string& accountNumber, double amount) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            if (it->second.balance >= amount) {
                it->second.balance -= amount;
                std::cout << "Withdrew " << amount << " from account " << accountNumber << std::endl;
            } else {
                std::cout << "Insufficient funds.\n";
            }
        } else {
            std::cout << "Account not found.\n";
        }
    }

    // Transfers money between accounts
    void transfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
        auto fromIt = accounts.find(fromAccount);
        auto toIt = accounts.find(toAccount);
        if (fromIt != accounts.end() && toIt != accounts.end()) {
            if (fromIt->second.balance >= amount) {
                fromIt->second.balance -= amount;
                toIt->second.balance += amount;
                std::cout << "Transferred " << amount << " from " << fromAccount << " to " << toAccount << std::endl;
            } else {
                std::cout << "Insufficient funds.\n";
            }
        } else {
            std::cout << "One or both accounts not found.\n";
        }
    }

    // Retrieves the balance of an account
    double getBalance(const std::string& accountNumber) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            return it->second.balance;
        }
        std::cout << "Account not found.\n";
        return 0.0;
    }
};

// Main function with menu-driven interface
int main() {
    Bank bank;
    while (true) {
        std::cout << "\n=== Online Banking System ===\n";
        std::cout << "1. Create account\n";
        std::cout << "2. Log in\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string name, password;
            double initialDeposit;
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Enter password: ";
            std::cin >> password;
            std::cout << "Enter initial deposit: ";
            std::cin >> initialDeposit;
            bank.createAccount(name, password, initialDeposit);
        } else if (choice == 2) {
            std::string accNum, password;
            std::cout << "Enter account number: ";
            std::cin >> accNum;
            std::cout << "Enter password: ";
            std::cin >> password;
            if (bank.verifyLogin(accNum, password)) {
                std::cout << "Login successful!\n";
                while (true) {
                    std::cout << "\n=== Account Menu ===\n";
                    std::cout << "1. Deposit\n";
                    std::cout << "2. Withdraw\n";
                    std::cout << "3. Transfer\n";
                    std::cout << "4. View balance\n";
                    std::cout << "5. Log out\n";
                    std::cout << "Enter choice: ";
                    int subChoice;
                    std::cin >> subChoice;

                    if (subChoice == 1) {
                        double amount;
                        std::cout << "Enter amount to deposit: ";
                        std::cin >> amount;
                        bank.deposit(accNum, amount);
                    } else if (subChoice == 2) {
                        double amount;
                        std::cout << "Enter amount to withdraw: ";
                        std::cin >> amount;
                        bank.withdraw(accNum, amount);
                    } else if (subChoice == 3) {
                        std::string targetAcc;
                        double amount;
                        std::cout << "Enter target account number: ";
                        std::cin >> targetAcc;
                        std::cout << "Enter amount to transfer: ";
                        std::cin >> amount;
                        bank.transfer(accNum, targetAcc, amount);
                    } else if (subChoice == 4) {
                        double balance = bank.getBalance(accNum);
                        std::cout << "Balance: " << balance << std::endl;
                    } else if (subChoice == 5) {
                        std::cout << "Logged out.\n";
                        break;
                    } else {
                        std::cout << "Invalid choice. Try again.\n";
                    }
                }
            } else {
                std::cout << "Invalid account number or password.\n";
            }
        } else if (choice == 3) {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}