/*
rec03.cpp
Herman Lin
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


//=======//
//Task #1//
//=======//
struct AccountStruct {
    string name;
    int accNumber;
};

//=======//
//Task #2//
//=======//
class AccountClass {
    private:
//===========//
//Task #3 + 4//
//===========//
    class Transaction {
        friend ostream& operator<<(ostream& os, const Transaction& transaction) {
            os << transaction._transactionType << ": " << transaction._transactionAmount;
            return os;
        }
    public:
        Transaction(char transaction, int amount) :
            _transactionType(transaction), _transactionAmount(amount)
        {}
    private:
        /*=============
        transactionType
        - d = deposit
        - w = withdrawal
        =============*/
        char _transactionType;
        int _transactionAmount;
    };

    string _name;
    int _accNumber;

    vector<Transaction> _transactionHistory;
    int _balance;
    
public:
    AccountClass(const string& accountName, int accountNumber) :
        _name(accountName), _accNumber(accountNumber)
    {}

    friend ostream& operator<<(ostream& os, const AccountClass& account) {
        os << account._name << "\t" << account._accNumber << endl;
        for (const Transaction& transaction : account._transactionHistory) {
            os << transaction << endl;
        }
        return os;
    }
    
    //*** Uncomment these lines to test Task2PartA ***
    const string& getName() const { return _name; }
    const int getAccNumber() const { return _accNumber; }

    void display(ostream& os = cout) const {
        os << _name << "\t" << _accNumber << endl;
    }

    void displayTransactions(const vector<Transaction> transactions) {

    }

    void deposit(int amount) {
        _transactionHistory.emplace_back('d', amount);
        _balance += amount;
        cout << "\nAccount Number: " << _accNumber
            << "\nAmount Deposited: " << amount
            << "\nNew Balance: " << _balance << endl;
    }

    void withdraw(int amount) {
        if (amount <= _balance) {
            _transactionHistory.emplace_back('w', amount);
            _balance -= amount;
            cout << "\nAccount Number: " << _accNumber
            << "\nAmount Withdrawn: " << amount
            << "\nNew Balance: " << _balance << endl;
        }
        else {
            cerr << "\nInsufficient funds in bank account"
                << "\nCannot withdraw: " << amount << endl;
        }
    }
};


//prototypes
void openFile(ifstream& stream);
void openTransactionFile(ifstream& transStream);
void displayAccStructVector(const vector<AccountStruct>& Accounts);
void task1PartA(ifstream& accountsStream, vector<AccountStruct>& AccountsStructVec);
void task1PartB(ifstream& accountsStream, vector<AccountStruct>& AccountsStructVec);
void task2PartAConstructorTest(ifstream& accountsStream, vector<AccountClass>& AccountsClassVec);
void task2PartAGetTest(const vector<AccountClass>& AccountsClassVec);
void task2PartB(const vector<AccountClass>& AccountsClassVec);
void task2PartC(const vector<AccountClass>& AccountsClassVec);
void task2PartD(ifstream& accountsStream, vector<AccountClass>& AccountsClassVec);
void task2PartE(ifstream& accountsStream, vector<AccountClass>& AccountsClassVec);
void task3Deposit(vector<AccountClass>& TransactionsAccountsVec, int accNum, int amount);
void task3Withdraw(vector<AccountClass>& TransactionsAccountsVec, int accNum, int amount);


int main() {
    ifstream accountsStream;

    /*===========
    Task 1 Driver
    ===========*/
    vector<AccountStruct> AccountsStructVec;
  
    //Part A  
    task1PartA(accountsStream, AccountsStructVec);

    //Part B
    AccountsStructVec.clear();
    task1PartB(accountsStream, AccountsStructVec);

    /*===========
    Task 2 Driver
    ===========*/
    vector<AccountClass> AccountsClassVec;
   
    //Part A Constructor Test
    //task2PartAConstructorTest(accountsStream, AccountsClassVec);

    //Part D
    //task2PartD(accountsStream, AccountsClassVec);

    //Part E
    task2PartE(accountsStream, AccountsClassVec);

    //Part A 
    task2PartAGetTest(AccountsClassVec);
    
    //Part B
    task2PartB(AccountsClassVec);

    //Part C
    task2PartC(AccountsClassVec);

    /*===========
    Task 4 Driver
    ===========*/
    cout << "\n======================" << endl;
    vector<AccountClass> TransactionsAccountsVec;


    string command, newAccName;
    int newAccNum, accNum, transAmount;
    openTransactionFile(accountsStream);
    
    while(accountsStream >> command) {
        if (command == "Account") {
            accountsStream >> newAccName >> newAccNum;
            TransactionsAccountsVec.emplace_back(newAccName, newAccNum);
            cout << "\nNew Account Made: " << newAccName << "\t" << newAccNum <<endl;
        }
        else {

            accountsStream >> accNum >> transAmount;
            if (command == "Deposit") {
                task3Deposit(TransactionsAccountsVec, accNum, transAmount);
            }
            else if (command == "Withdraw") {
                task3Withdraw(TransactionsAccountsVec, accNum, transAmount);
            }
        }
    }
    accountsStream.close();
}

/*==================
File Opener Function
- Open the 'accounts.txt' file
==================*/
void openFile(ifstream& stream) {
    stream.clear();
    stream.open("accounts.txt");
    if (!stream) {
        cerr << "Could not find file 'accounts.txt'" << endl;
        exit(1);
    }
}

/*==================
File Opener Function
- Open the 'transactions.txt' file
==================*/
void openTransactionFile(ifstream& transStream) {
    transStream.clear();
    transStream.open("transactions.txt");
    if (!transStream) {
        cerr << "Could not find file 'transactions.txt'" << endl;
        exit(1);
    }
}

/*====================================
Account Struct Vector Display Function
====================================*/
void displayAccStructVector(const vector<AccountStruct>& Accounts) {
    for (const AccountStruct& account : Accounts) {
        cout << account.name << "\t" << account.accNumber << endl;
    }
}

/*====================
Task 1 Part A Function
====================*/
void task1PartA(ifstream& accountsStream, vector<AccountStruct>& AccountsStructVec) {
    string accountHolder;
    int accountNumber;

    openFile(accountsStream);
    while (accountsStream >> accountHolder >> accountNumber) {
        AccountStruct newAcc;
        newAcc.name = accountHolder;
        newAcc.accNumber = accountNumber;
        AccountsStructVec.push_back(newAcc);
    }
    accountsStream.close();
    cout << "Task 1 - Part A:" << endl;
    displayAccStructVector(AccountsStructVec);
}

/*====================
Task 1 Part B Function
====================*/
void task1PartB(ifstream& accountsStream, vector<AccountStruct>& AccountsStructVec) {
    string accountHolder;
    int accountNumber;

    openFile(accountsStream);
    while (accountsStream >> accountHolder >> accountNumber) {
        AccountStruct newAcc{accountHolder, accountNumber};
        AccountsStructVec.push_back(newAcc);
    }
    accountsStream.close();
    cout << "\nTask 1 - Part B:" << endl;
    displayAccStructVector(AccountsStructVec);
}

/*=====================================
Task 2 Part A Constructor Test Function
=====================================*/
void task2PartAConstructorTest(ifstream& accountsStream, vector<AccountClass>& AccountsClassVec) {
    string accountHolder;
    int accountNumber;

    openFile(accountsStream);
    while (accountsStream >> accountHolder >> accountNumber) {
        AccountClass newAcc(accountHolder, accountNumber);
        AccountsClassVec.push_back(newAcc);
    }
    accountsStream.close();
}

/*================================
Task 2 Part A Getter Test Function
================================*/
void task2PartAGetTest(const vector<AccountClass>& AccountsClassVec) {
    cout << "\nTask 2 - Part A:" << endl;
    for (const AccountClass& account : AccountsClassVec) {
        cout << account.getName() << "\t" << account.getAccNumber() << endl;
    }
}

/*====================
Task 2 Part B Function
====================*/
void task2PartB(const vector<AccountClass>& AccountsClassVec) {
    cout << "\nTask 2 - Part B:" << endl;
    for (const AccountClass& account : AccountsClassVec) {
        account.display();
    }
}

/*====================
Task 2 Part C Function
====================*/
void task2PartC(const vector<AccountClass>& AccountsClassVec) {
    cout << "\nTask 2 - Part C:" << endl;
    for (const AccountClass& account : AccountsClassVec) {
        cout << account;
    }

}

/*====================
Task 2 Part D Function
====================*/
void task2PartD(ifstream& accountsStream, vector<AccountClass>& AccountsClassVec) {
    string accountHolder;
    int accountNumber;

    openFile(accountsStream);
    while (accountsStream >> accountHolder >> accountNumber) {
        AccountsClassVec.push_back(AccountClass(accountHolder, accountNumber));
    }
    accountsStream.close();
}

/*===================
Task 2 Part E Fuction
===================*/
void task2PartE(ifstream& accountsStream, vector<AccountClass>& AccountsClassVec) {
    string accountHolder;
    int accountNumber;

    openFile(accountsStream);
    while (accountsStream >> accountHolder >> accountNumber) {
        AccountsClassVec.emplace_back(accountHolder, accountNumber);
    }
    accountsStream.close();
}

/*=====================
Task 3 Deposit Function
=====================*/
void task3Deposit(vector<AccountClass>& TransactionsAccountsVec, int accNum, int transAmount) {
    bool accNotFound = true;
    for (AccountClass& account : TransactionsAccountsVec) {
        if (account.getAccNumber() == accNum) {
            account.deposit(transAmount);
            accNotFound = false;
            break;
        }
    }
    if (accNotFound) {
        cerr << "No account found with account number: " << accNum << endl;
    }
}

/*======================
Task 3 Withdraw Function
======================*/
void task3Withdraw(vector<AccountClass>& TransactionsAccountsVec, int accNum, int transAmount) {
    bool accNotFound = true;
    for (AccountClass& account : TransactionsAccountsVec) {
        if (account.getAccNumber() == accNum) {
            account.withdraw(transAmount);
            accNotFound = false;
            break;
        }
    }
    if (accNotFound) {
        cerr << "No account found with account number: " << accNum << endl;
    }
}