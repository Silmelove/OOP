#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Transaction {
    double amount;
    string type;
    string date;
public:
    Transaction(double amt, string t, string d) : amount(amt), type(t), date(d) {}
    void displayTransaction() {
        cout << "   [" << type << "] " << amount << " on " << date << endl;
    }
};

class Account {
protected:
    string accountNumber;
    string ownerName;
    double balance;
    vector<Transaction> transactions;
public:
    Account(string accNum, string owner, double bal = 0)
        : accountNumber(accNum), ownerName(owner), balance(bal) {}

    virtual ~Account() {}

    virtual void withdraw(double amount) {
        if (amount > balance) {
            cout << "Khong du tien de rut!\n";
        }
        else {
            balance -= amount;
            transactions.push_back(Transaction(amount, "Withdraw", "2025-09-16"));
        }
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction(amount, "Deposit", "2025-09-16"));
    }

    virtual void displayInfo() {
        cout << "Account: " << accountNumber << " | Owner: " << ownerName
            << " | Balance: " << balance << endl;
        for (auto& t : transactions) t.displayTransaction();
    }

    Account& operator+=(Transaction t) {
        transactions.push_back(t);
        return *this;
    }

    bool operator==(const Account& other) const {
        return this->balance == other.balance;
    }

    double getBalance() const { return balance; }
};

class SavingsAccount : public Account {
    double interestRate; 
public:
    SavingsAccount(string accNum, string owner, double bal, double rate)
        : Account(accNum, owner, bal), interestRate(rate) {}

    void withdraw(double amount) override {
        if (amount > balance) {
            cout << "Khong du tien de rut tu SavingAccount!\n";
        }
        else if (amount > 5000) {
            cout << "Vuot han muc rut toi da 5000!\n";
        }
        else {
            balance -= amount;
            transactions.push_back(Transaction(amount, "Withdraw (Saving)", "2025-09-16"));
        }
    }

    void applyInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        transactions.push_back(Transaction(interest, "Interest", "2025-09-16"));
    }

    void displayInfo() override {
        cout << "[Savings] Account: " << accountNumber << " | Owner: " << ownerName
            << " | Balance: " << balance << " | Rate: " << interestRate << "%" << endl;
        for (auto& t : transactions) t.displayTransaction();
    }
};

class Customer {
    string customerID;
    string name;
    vector<Account*> accounts;
public:
    Customer(string id, string n) : customerID(id), name(n) {}

    void openAccount(Account* acc) {
        accounts.push_back(acc);
    }

    double getTotalBalance() {
        double sum = 0;
        for (auto acc : accounts) sum += acc->getBalance();
        return sum;
    }

    void displayCustomerInfo() {
        cout << "Customer: " << name << " (" << customerID << ")" << endl;
        for (auto acc : accounts) acc->displayInfo();
        cout << "Total Balance: " << getTotalBalance() << endl;
    }
};

int main() {
    Customer c1("C001", "Nguyen Van A");

    Account* acc1 = new Account("A1001", "Nguyen Van A", 10000);
    SavingsAccount* sacc1 = new SavingsAccount("S2001", "Nguyen Van A", 5000, 5);

    c1.openAccount(acc1);
    c1.openAccount(sacc1);
    acc1->deposit(2000);
    acc1->withdraw(3000);
    sacc1->withdraw(6000); 
    sacc1->withdraw(4000); 
    sacc1->applyInterest();

    if (*acc1 == *sacc1) cout << "Hai tai khoan bang nhau ve so du\n";
    else cout << "Hai tai khoan khac nhau ve so du\n";

    c1.displayCustomerInfo();

    delete acc1;
    delete sacc1;
    return 0;
}
