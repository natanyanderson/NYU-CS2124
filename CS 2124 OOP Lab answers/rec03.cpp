/* Natanya Anderson
  rec03_start.cpp
  spring 2024
*/

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


// Task 1
// Define an Account struct
struct Account {
    string accountName;
    int accountNumber;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
class Accountinfo {
    // Output operator declared as a friend to access private members
    friend ostream& operator<<(ostream& os, const Accountinfo &acc);

private:
    string accountName;
    int accountNumber;
public:
    Accountinfo(const string &accName, int accNum) : accountName(accName), accountNumber(accNum) {}
    string getName() const { return accountName; }
    int getNumber() const { return accountNumber; }
};
ostream& operator<<(ostream& os, const Accountinfo &acc) {
    os << "Account Name: " << acc.getName() << ", Account Number: " << acc.getNumber();
    return os;
    os << "Account Name: " << acc.accountName << ", Account Number: " << acc.accountNumber;
    return os;
}


// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
class Transaction {
public:
   enum class Type { Deposit, Withdrawal };
   Type type;
   double amount;

   Transaction(Type t, double amt) : type(t), amount(amt) {}
};
// Output operator for Transaction class
ostream& operator<<(ostream& os, const Transaction& trans) {
    os << (trans.type == Transaction::Type::Deposit ? "Deposit: " : "Withdrawal: ") << trans.amount;
    return os;
}
class Accountinfo2 {
    friend ostream& operator<<(ostream& os, const Accountinfo2& acc);
private:
    vector<Transaction> transactions;
    double balance;
    string accountName;
    int accountNumber;
public:

    Accountinfo2(const string &accName, int accNum) : accountName(accName), accountNumber(accNum) {}

    // Methods to deposit and withdraw, modifying the balance
    void deposit(double amount) {
        transactions.emplace_back(Transaction::Type::Deposit, amount);
        balance += amount;
    }

    void withdrawal(double amount) {
        transactions.emplace_back(Transaction::Type::Withdrawal, amount);
        balance -= amount;
    }


    // Getters (might be used for other purposes, not needed for friend output operator)
    double getBalance() const { return balance; }
    const vector<Transaction>& getTransactions() const { return transactions; }
};
ostream& operator<<(ostream& os, const Accountinfo2& acc) {
    os << "Account balance: " << acc.balance << "\n";
    os << "Transaction history:\n";
    for (const auto& trans : acc.transactions) {
        os << trans << "\n";
    }
    return os;
}

Accountinfo2* findAccount(vector<Accountinfo2>& accounts, int accountNumber) {
    for (Accountinfo2& acc : accounts) {
        if (acc.getBalance() == accountNumber) {
            return &acc; // Return a pointer to the account
        }
    }
    return nullptr; // Return nullptr if not found
}

// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)
class Accountinfo3{
    friend ostream& operator<<(ostream& os, const Accountinfo3& acc);
public:
    class Transaction {
    public:
        enum class Type { Deposit, Withdrawal };
        Type type;
        double amount;

        Transaction(Type t, double amt) : type(t), amount(amt) {}
    };
private:
    vector<Transaction> transactions;
    double balance;
    string accountName;
    int accountNumber;

public:
    Accountinfo3(const string &accName, int accNum) : accountName(accName), accountNumber(accNum) {}

    // Methods to deposit and withdraw, modifying the balance
    void deposit(double amount) {
        transactions.emplace_back(Transaction::Type::Deposit, amount);
        balance += amount;
    }

    void withdrawal(double amount) {
        transactions.emplace_back(Transaction::Type::Withdrawal, amount);
        balance -= amount;
    }


    // Getters (might be used for other purposes, not needed for friend output operator)
    double getBalance() const { return balance; }
    const vector<Transaction>& getTransactions() const { return transactions; }
};
ostream& operator<<(ostream& os, const Accountinfo3::Transaction& trans) {
    // Use the fully qualified name for Transaction as it's nested inside Account
    os << (trans.type == Accountinfo3::Transaction::Type::Deposit ? "Deposit: " : "Withdrawal: ") << trans.amount;
    return os;
}

Accountinfo3* findAccount2(vector<Accountinfo3>& accounts, int accountNumber) {
    for (Accountinfo3& acc : accounts) {
        if (acc.getBalance() == accountNumber) {
            return &acc; // Return a pointer to the account
        }
    }
    return nullptr; // Return nullptr if not found
}
ostream& operator<<(std::ostream& os, const Accountinfo3& acc) {
    os << "Account Balance: " << acc.balance << "\nTransactions:\n";
    for (const auto& trans : acc.transactions) {
        os << trans << "\n"; // This will use the output operator defined above for Transaction
    }
    return os;
}

// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)

int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream file;
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    vector<Account> accountInfo;
    string accountName;
    int accountNum;
    while (file >> accountName >> accountNum) {
        Account newAccount;
        newAccount.accountName = accountName;
        newAccount.accountNumber = accountNum;
        accountInfo.push_back(newAccount);

    }
    file.close(); // Close the file

    // Display the account information
    for (const Account& acc : accountInfo) {
        cout << "Account Name: " << acc.accountName << ", Account Number: " << acc.accountNumber << endl;
    }
    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accountInfo.clear();
    file.close();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    while (file >> accountName >> accountNum) {
        Account newAccount{accountName, accountNum};
        accountInfo.push_back(newAccount); // Using curly brace initializers
    }
    for (const Account& acc : accountInfo) {
        cout << "Account Name: " << acc.accountName << ", Account Number: " << acc.accountNumber << endl;
    }
    file.close();

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    file.close();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    vector<Accountinfo> accountinformation;
    // Read the file content and populate the accounts vector
    while (file >> accountName >> accountNum) {
        Accountinfo newAccount{accountName, accountNum};
        accountinformation.push_back(newAccount);
    }
        // Display the account information
    for (const Accountinfo& acc : accountinformation) {
        cout << "Account Name: " << acc.getName() << ", Account Number: " << acc.getNumber() << endl;
    }

    file.close(); // Close the file


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    accountinformation.clear();
    file.close();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    // Read the file content and populate the accounts vector
    while (file >> accountName >> accountNum) {
        Accountinfo newAccount{accountName, accountNum};
        accountinformation.push_back(newAccount);
    }
    // Display the account information
    for (const Accountinfo& acc : accountinformation) {
        cout << acc << endl;
    }

    file.close();

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    accountinformation.clear();
    file.close();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    // Read the file content and populate the accounts vector
    while (file >> accountName >> accountNum) {
        Accountinfo newAccount{accountName, accountNum};
        accountinformation.push_back(newAccount);
    }
    // Display the account information
    for (const Accountinfo& acc : accountinformation) {
        cout << acc << endl;
    }

    file.close();

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    accountinformation.clear();
    file.close();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    while (file >> accountName >> accountNum) {
        accountinformation.push_back(Accountinfo(accountName, accountNum));// Using constructor
    }
    // Display the account information
    for (const Accountinfo& acc : accountinformation) {
        cout << acc << endl;
    }

    file.close();

    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    accountinformation.clear();
    file.close();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    // Read the file content and populate the accounts vector
    while (file >> accountName >> accountNum) {
        accountinformation.emplace_back(accountName, accountNum); // Using constructor
    }
        // Display the account information
    for (const Accountinfo& acc : accountinformation) {
        cout << acc << endl;
    }

    file.close();


    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
    ifstream filetransactions;
    filetransactions.open("transactions.txt");
    if (!filetransactions) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    vector<Accountinfo2> accounts; // Use a vector to store accounts
    string command;
    string accountName2;
    int accountNumber;
    double amount;

    cout << "Transaction nested in Account;\n" << endl;
    while (filetransactions >> command) {
        if (command == "Account") {
            filetransactions >> accountName2 >> accountNumber;
            Accountinfo2 newAccount{accountName2, accountNumber};
            accounts.push_back(newAccount);
        } else if (command == "Deposit") {
            filetransactions >> accountNumber >> amount;
            Accountinfo2* acc = findAccount(accounts, accountNumber);
            if (acc != nullptr) {
                acc->deposit(amount);
                cout << accountName2 << "\t"  << accountNumber << ":\n" << "deposit " << amount << endl;
            } else {
                cerr << "Account# " << accountNumber << " not found for deposit." << endl;
            }
        } else if (command == "Withdraw") {
            filetransactions >> accountNumber >> amount;
            Accountinfo2* acc = findAccount(accounts, accountNumber);
            if (acc != nullptr) {
                if (acc->getBalance() >= amount) {
                    acc->withdrawal(amount);
                    cout << accountName2 << "\t"  << accountNumber << ":\n" << "deposit " << amount << endl;
                } else {
                    cerr << "Account# " << accountNumber << " has only " << acc->getBalance() <<  " Insufficient for withdrawl of " << amount << endl;
                }
            } else {
                cerr << "Account#" << accountNumber << " not found for withdrawal." << endl;
            }
        }
    }

    filetransactions.close(); // Close the file after reading is complete

    // Display the account information for each account
    for (const Accountinfo2& acc: accounts) {
        cout << acc << endl;
    }

    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

    filetransactions.close();
    vector<Accountinfo3> accounts2; // Use a vector to store accounts
    string command2;
    string accountName3;
    int accountNumber2;
    double amount1;
    filetransactions.open("transactions.txt");
    if (!filetransactions) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    cout << "Transaction nested in Account;\n" << endl;
    while (filetransactions >> command2) {
        if (command2 == "Account") {
            filetransactions >> accountName3 >> accountNumber2;
            Accountinfo3 newAccount{accountName3, accountNumber2};
            accounts2.push_back(newAccount);
        } else if (command == "Deposit") {
            filetransactions >> accountNumber2 >> amount1;
            Accountinfo3* acc = findAccount2(accounts2, accountNumber2);
            if (acc != nullptr) {
                acc->deposit(amount1);
                cout << accountName3 << "\t"  << accountNumber2 << ":\n" << "deposit " << amount1 << endl;
            } else {
                cerr << "Account number " << accountNumber2 << " not found for deposit." << endl;
            }
        } else if (command2 == "Withdraw") {
            filetransactions >> accountNumber2 >> amount1;
            Accountinfo3* acc = findAccount2(accounts2, accountNumber2);
            if (acc != nullptr) {
                if (acc->getBalance() >= amount1) {
                    acc->withdrawal(amount1);
                } else {
                    cerr << "Account# " << accountNumber2 << " has only " << acc->getBalance() <<  " Insufficient for withdrawl of " << amount1 << endl;
                }
            } else {
                cerr << "Account number " << accountNumber2 << " not found for withdrawal." << endl;
            }
        }
    }

    filetransactions.close(); // Close the file after reading is complete

    // Display the account information for each account
    for (const Accountinfo3& acc : accounts2) {
        cout << acc << endl;
    }
    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

};