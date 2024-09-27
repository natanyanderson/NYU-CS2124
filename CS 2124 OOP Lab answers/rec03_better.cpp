/*
  rec03_start.cpp
  2024 Fall
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
    int accountNum;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account2 {
    friend ostream& operator<<(ostream& os, const Account2& acc);
public:
    Account2(const string& name, int num) : accName(name), accNumber(num) {}
    const string& getName() const {return accName;}
    int getNum() const {return accNumber;}
private:
    string accName;
    int accNumber;
};
ostream& operator<<(ostream& os, const Account2& acc) {
    //os << "Account Name: " << acc.getName() << "Account Num: " << acc.getNum() << endl;
    //return os;
    os << "Account Name: "  << acc.accName << "Account Num: " << acc.accNumber << endl;
    return os;
}

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".
class Transaction {
    friend ostream& operator<<(ostream& os, const Transaction& trans);
private:
    double amount;
    string transactionType;
public:
    Transaction(const string& transType, double amt) : transactionType(transType), amount(amt) {}
};
// Output operator for Transaction class
ostream& operator<<(ostream& os, const Transaction& trans) {
    os << "\t" << trans.transactionType << " " << trans.amount << "\n";
    return os;
};

class Account3 {
    friend ostream& operator<<(ostream& os, const Account3& acc);
private:
    vector<Transaction> transactions;
    double balance;
    string accountName;
    int accountNumber;
public:
    Account3(const string &accName, int accNum) : accountName(accName), accountNumber(accNum) {}
    int getAccountNum() const {return accountNumber;}
    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back(" Deposit", amount);
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Account# " << accountNumber << " has only $" << balance << ". Insufficient funds for withdrawal of $" << amount << endl;
        } else {
            balance -= amount;
            transactions.emplace_back(" Withdrawal", amount);
        }
    }
};
//output for Account3
ostream& operator<<(ostream& os, const Account3& acc) {
    os << acc.accountName << "\t" << acc.accountNumber << ":\n";
    for (const Transaction& t : acc.transactions) {
        os << t;
    }
    if (acc.transactions.empty()) {
        os << "\n";
    }
    return os;
}

// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class Account4 {
public:
    class Transaction2 {
        friend ostream& operator<<(ostream& os, const Transaction2& trans);
    private:
        double amount;
        string transactionType;
    public:
        Transaction2(const string& transType, double amt) : transactionType(transType), amount(amt) {}
    };
    friend ostream& operator<<(ostream& os, const Account4& acc);
private:
    vector<Transaction2> transactions;
    double balance;
    string accountName;
    int accountNumber;
public:
    Account4(const string &accName, int accNum) : accountName(accName), accountNumber(accNum) {}
    int getAccountNum() const {return accountNumber;}
    const string& getAccountName() const {return accountName;}

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back(" Deposit", amount);
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Account# " << accountNumber << " has only $" << balance << ". Insufficient funds for withdrawal of $" << amount << endl;
        } else {
            balance -= amount;
            transactions.emplace_back(" Withdrawal", amount);
        }
    }
};
//output for Account4
ostream& operator<<(ostream& os, const Account4& acc) {
    os << acc.accountName << "\t" << acc.getAccountNum() << ":\n";
    for (const Account4::Transaction2& t : acc.transactions) {
        os << t;
    }
    if (acc.transactions.empty()) {
        os << "\n";
    }
    return os;
}
// Output operator for Transaction class
ostream& operator<<(ostream& os, const Account4::Transaction2& trans) {
    os << "\t" << trans.transactionType << " " << trans.amount << "\n";
    return os;
};
// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.


int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";
    ifstream file;
    string lines;
    vector<Account> accountInfo;
    file.open("accounts.txt");
    if (!file) {
        cerr << "Can't read file" << endl;
    }
    string accName;
    int accNum;
    while (file >> accName >> accNum) {
        Account acc;
        acc.accountName = accName;
        acc.accountNum = accNum;
        accountInfo.push_back(acc);
    }
    file.close();
    for (const Account& acc : accountInfo) {
        cout << "Account Name: " << acc.accountName << ", Account Number: " << acc.accountNum << endl;
    }

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";
    accountInfo.clear();
    file.open("accounts.txt");
    if (!file) {
        cerr << "Can't read file" << endl;
    }
    while (file >> accName >> accNum) {
        Account acc { accName, accNum}; //curly bracket initializer
        accountInfo.push_back(acc);
    }
    for (const Account& acc : accountInfo) {
        cout << "Account Name: " << acc.accountName << ", Account Number: " << acc.accountNum << endl;
    }
    file.close();
    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
    file.open("accounts.txt");
    if (!file) {
        cerr << "Can't read file" << endl;
    }
    vector<Account2> accountinformation;
    // Read the file content and populate the accounts vector
    while (file >> accName >> accNum) {
        Account2 newAccount(accName, accNum);
        accountinformation.push_back(newAccount);
    }
    // Display the account information
    for (const Account2& acc : accountinformation) {
        cout << "Account Name: " << acc.getName() << ", Account Number: " << acc.getNum() << endl;
    }
    file.close();


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    accountinformation.clear();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    while (file >> accName >> accNum) {
        Account2 newAccount(accName, accNum);
        accountinformation.push_back(newAccount);
    }

    for (const Account2& acc : accountinformation) {
        cout << acc;
    }
    file.close();

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
    accountinformation.clear();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    while (file >> accName >> accNum) {
        Account2 newAccount(accName, accNum);
        accountinformation.push_back(newAccount);
    }
    for (const Account2& acc : accountinformation) {
        cout << acc;
    }
    file.close();

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
    accountinformation.clear();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    while (file >> accName >> accNum) {
        accountinformation.push_back(Account2(accName, accNum));
    }
    for (const Account2& acc : accountinformation) {
        cout << acc;
    }
    file.close();

    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
    accountinformation.clear();
    file.open("accounts.txt");
    if (!file) {
        cout << "there is no filename account.txt\n";
        exit(1);
    }
    while (file >> accName >> accNum) {
        accountinformation.emplace_back(accName, accNum);
    }
    // Display the account information
    for (const Account2& acc : accountinformation) {
        cout << acc;
    }
    file.close();

    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
    vector<Account3> accounts;
    file.open("transactions.txt");

    while (file >> lines) {
        if (lines == "Account") {
            string owner;
            int number;
            file >> owner >> number;
            accounts.emplace_back(owner, number);
        } else if (lines == "Deposit" || lines == "Withdraw") {
            int number;
            double amount;
            file >> number >> amount;
            //bool transactionCompleted = false;
            for (Account3& account : accounts) {
                if (account.getAccountNum() == number) {
                    if (lines == "Deposit") {
                        account.deposit(amount);
                        //transactionCompleted = true;
                    } else if (lines == "Withdraw") {
                        account.withdraw(amount);
                        //transactionCompleted = true;
                    }
                }
            }
        }
    }
    file.close();
    // Output all accounts
    for (const Account3& acc : accounts) {
        cout << acc << endl;
    }

    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
    vector<Account4> accounts2;
    file.open("transactions.txt");

    while (file >> lines) {
        if (lines == "Account") {
            string owner;
            int number;
            file >> owner >> number;
            accounts2.emplace_back(owner, number);
        } else if (lines == "Deposit" || lines == "Withdraw") {
            int number;
            double amount;
            file >> number >> amount;
            //bool transactionCompleted = false;
            for (Account4& account : accounts2) {
                if (account.getAccountNum() == number) {
                    if (lines == "Deposit") {
                        account.deposit(amount);
                        //transactionCompleted = true;
                    } else if (lines == "Withdraw") {
                        account.withdraw(amount);
                        //transactionCompleted = true;
                    }
                }
            }
        }
    }

    // Output all accounts
    for (const Account4& acc : accounts2) {
        cout << acc << endl;
    }

    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";


}

