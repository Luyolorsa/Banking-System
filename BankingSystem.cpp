#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Define a struct to represent a user account
struct Account {
    string username;
    string password;
    double balance;
    vector<string> transactionHistory;
};

// Define a map to store user accounts
map<string, Account> accounts;

// Function to create a new user account
void createAccount() {
    string accountNumber, username, password;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    Account account = {username, password, 0.0};
    accounts[accountNumber] = account;
    cout << "Account created successfully!" << endl;
}

// Function to login to an existing account
string login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    for (auto& account : accounts) {
        if (account.second.username == username && account.second.password == password) {
            return account.first;
        }
    }
    cout << "Invalid username or password" << endl;
    return "";
}

// Function to deposit money into an account
void deposit(string accountNumber) {
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    accounts[accountNumber].balance += amount;
    accounts[accountNumber].transactionHistory.push_back("Deposit: " + to_string(amount));
    cout << "Deposit successful!" << endl;
}

// Function to withdraw money from an account
void withdraw(string accountNumber) {
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (accounts[accountNumber].balance >= amount) {
        accounts[accountNumber].balance -= amount;
        accounts[accountNumber].transactionHistory.push_back("Withdrawal: " + to_string(amount));
        cout << "Withdrawal successful!" << endl;
    } else {
        cout << "Insufficient funds" << endl;
    }
}

// Function to transfer money between accounts
void transfer(string senderAccountNumber, string recipientAccountNumber, double amount) {
    if (accounts[senderAccountNumber].balance >= amount) {
        accounts[senderAccountNumber].balance -= amount;
        accounts[recipientAccountNumber].balance += amount;
        accounts[senderAccountNumber].transactionHistory.push_back("Transfer to " + recipientAccountNumber + ": " + to_string(amount));
        accounts[recipientAccountNumber].transactionHistory.push_back("Transfer from " + senderAccountNumber + ": " + to_string(amount));
        cout << "Transfer successful!" << endl;
    } else {
        cout << "Insufficient funds" << endl;
    }
}

// Function to check account balance
void checkBalance(string accountNumber) {
    cout << "Account balance: " << accounts[accountNumber].balance << endl;
}

// Function to display account statement
void displayStatement(string accountNumber) {
    cout << "Account statement:" << endl;
    for (const auto& transaction : accounts[accountNumber].transactionHistory) {
        cout << transaction << endl;
    }
}

// Function to update account information
void updateAccount(string accountNumber) {
    cout << "Enter new username: ";
    cin >> accounts[accountNumber].username;
    cout << "Enter new password: ";
    cin >> accounts[accountNumber].password;
    cout << "Account information updated successfully!" << endl;
}

// Function to delete an account
void deleteAccount(string accountNumber) {
    accounts.erase(accountNumber);
    cout << "Account deleted successfully!" << endl;
}

int main() {
    int choice;
    string accountNumber;

    while (true) {
        cout << "Banking System Menu:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                accountNumber = login();
                if (!accountNumber.empty()) {
                    while (true) {
                        cout << "Account Menu:" << endl;
                        cout << "1. Deposit" << endl;
                        cout << "2. Withdraw" << endl;
                        cout << "3. Check Balance" << endl;
                        cout << "4. Transfer" << endl;
                        cout << "5. Display Statement" << endl;
                        cout << "6. Update Account" << endl;
                        cout << "7. Delete Account" << endl;
                        cout << "8. Logout" << endl;
                        cout << "9. Cancel" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                deposit(accountNumber);
                                break;
                            case 2:
                                withdraw(accountNumber);
                                break;
                            case 3:
                                checkBalance(accountNumber);
                                break;
                            case 4: {
                                string recipientAccountNumber;
                                double amount;
                                cout << "Enter recipient account number: ";
                                cin >> recipientAccountNumber;
                                cout << "Enter amount to transfer: ";
                                cin >> amount;
                                transfer(accountNumber, recipientAccountNumber, amount);
                                break;
                            }
                            case 5:
                                displayStatement(accountNumber);
                                break;
                            case 6:
                                updateAccount(accountNumber);
                                break;
                            case 7:
                                deleteAccount(accountNumber);
                                accountNumber = "";
                                break;
                            case 8:
                                accountNumber = "";
                                break;
                            case 9:
                                cout << "Canceling operation. Returning to main menu." << endl;
                                accountNumber = "";
                                break;
                            default:
                                cout << "Invalid choice" << endl;
                        }
                    }
                }
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
