using namespace std;
#include <iostream>
#include <string>
#include <iomanip>

class Account{
    public:
        string accountNumber;
        string accountHolder;
        float balance;
    
        Account(std::string accountNumber, std::string accountHolder, float balance)
            : accountNumber(accountNumber), accountHolder(accountHolder), balance(balance) {
            // Constructor for the Account class
        }

    virtual void displayDetails(){
        // Display account details.
        cout << "Class name: " << typeid(this).name() << std::endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << std::fixed << std::setprecision(2) <<  "Balance: $" << balance << endl;
    }
    void deposit(float amount){
        // Deposit money into the account.
        if (amount > 0){
            balance += amount;
        }
        else {
            cout << "You can't add a negative deposit" << endl;
        }
    }
    void withdraw(float amount){
        // Withdraw money from the account (ensure sufficient balance).
        if (balance >= amount) {
            balance -= amount;
            // cout << "You have withdrawn $" << amount << ". You have $" << balance << " left." << endl;
        }
        else {
            cout << "You don't have enough money to withdraw $" << amount << endl;
        }
    }
};

class SavingsAccount: public Account {
    public:
        float interestRate;

        SavingsAccount(string accountNumber, string accountHolder, float balance, float interestRate)
            : Account(accountNumber, accountHolder, balance), interestRate(interestRate) {
            // Additional initialization for the SavingsAccount class
        }
        void displayDetails(){
            cout << "Account Details for Savings Account (ID: " << accountNumber << "): " << endl;
            cout << "   Holder: " << accountHolder << endl;
            cout << std::fixed << std::setprecision(2) << "   Balance: $" << balance << endl;
            cout << std::fixed << std::setprecision(2) << "   Interest Rate: " << float(interestRate*100) << "%" << endl;
        }

    void withdraw(float amount){
        // Withdraw money from the account (ensure sufficient balance).
        if (balance >= amount) {
            balance -= amount;
            // cout << "You have withdrawn $" << amount << ". You have $" << balance << " left." << endl;
        }
        else if((balance - amount) > 50) {
            // 50 is an arbitrary number
            balance -= amount;
        }
        else {
            cout << "You don't have enough money to withdraw $" << amount << endl;
        }
    }
};

class CurrentAccount: public Account {
    /*
        Derived class from the Account class.
        Additional properties: overdraftlimit. 
        Override the withdraw method to allow overdrafts up to the specified limit.
    */
    public:
        float overdraftLimit;
        CurrentAccount(string accountNumber, string accountHolder, float balance, float overdraftLimit)
            : Account(accountNumber, accountHolder, balance), overdraftLimit(overdraftLimit) {
            // Additional initialization for the SavingsAccount class
        }
        void displayDetails(){
            cout << "Account Details for Checking Account (ID: " << accountNumber << "): " << endl;
            cout << "   Holder: " << accountHolder << endl;
            cout << "   Balance: $" << balance << endl;
            cout << "   Overdraft Limit: $" << overdraftLimit << endl;
        }
        void withdraw(float amount){
            if (amount > (balance + overdraftLimit)){
                cout << "You cannot withdraw that much " << endl;
            }
            else{
                 balance -= amount;
            }
        }
        

};

CurrentAccount operator+(CurrentAccount current, SavingsAccount& savings) {
    if (savings.balance >= 300) {
        current.deposit(300);
        savings.withdraw(300);
    }
    return current;
}

int main() {

    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    cout << "Account Details after deposit and withdrawal: " << endl;

    savings.deposit(500);
    current.withdraw(1000);
    
    savings.displayDetails();
    current.displayDetails();

    // Transfer 300 from savings to current
    cout << "Account Details after transfer: " << endl;
    current = current + savings;

    savings.displayDetails();
    current.displayDetails();

   return 0;
}

