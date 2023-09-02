#include <iostream>
#include <string>

using namespace std ;

    class BankAccount {
    public:
        BankAccount(int account_number, double balance, const string& owner_name);
        void deposit(double amount);
        void withdraw(double amount);
        void display_account() const;

    private:
        int account_number;
        double balance;
        string owner_name;
    };

    BankAccount::BankAccount(int account_number, double balance, const string& owner_name)
        : account_number(account_number), balance(balance), owner_name(owner_name) {}

    void BankAccount::deposit(double amount) {
        balance += amount;
        cout << "Deposit of " << amount << " successful. New balance is " << balance << endl;
    }

    void BankAccount::withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal of " << amount << " done , New balance is " << balance  << endl;
        } else {
            cout << "Withdrawal of " << amount << " failed , Balance is " << balance << endl;
        }
    }

    void BankAccount::display_account() const {
        cout << "account number: " << account_number << endl;
        cout << "owner name: " << owner_name << endl;
        cout << "current balance: " << balance << endl;
    }



int main() {
    // Create a BankAccount object
   BankAccount account(1,50000, "vicki");

    // Display the account details
    account.display_account();

    // Deposit some money
    account.deposit(1000.0);

    // Withdraw some money
    account.withdraw(500.0);

    // Withdraw too much money
    account.withdraw(60000);

    return 0;
}