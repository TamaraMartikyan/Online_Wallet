#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

struct User {
    string username;
    string password;
    double balance;

    User() : username(""), password(""), balance(0.0) {}
    User(string u, string p) : username(u), password(p), balance(0.0) {}
};

unordered_map<string, User> users;

void loadUsersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "No saved user data found. Starting fresh.\n";
        return;
    }
    string username, password;
    double balance;
    while (file >> username >> password >> balance) {
        users[username] = User(username, password);
        users[username].balance = balance;
    }
    file.close();
}

void saveUsersToFile(const string& filename) {
    ofstream file(filename);
    for (const auto& pair : users) {
        const User& user = pair.second;
        file << user.username << " " << user.password << " " << user.balance << "\n";
    }
    file.close();
}

bool registerUser(const string& username, const string& password) {
    if (users.find(username) != users.end()) {
        return false;
    }
    users[username] = User(username, password);
    return true;
}

bool loginUser(const string& username, const string& password) {
    auto it = users.find(username);
    if (it == users.end()) return false;
    return it->second.password == password;
}

void transfer(const string& fromUser, const string& toUser, double amount) {
    if (!loginUser(fromUser, users[fromUser].password)) {
        cout << "Invalid sender credentials.\n";
        return;
    }
    if (users[fromUser].balance < amount) {
        cout << "Insufficient funds.\n";
        return;
    }
    if (users.find(toUser) == users.end()) {
        cout << "Receiver not found.\n";
        return;
    }
    users[fromUser].balance -= amount;
    users[toUser].balance += amount;
    cout << "Transfer successful.\n";
}

void showBalance(const string& username) {
    if (users.find(username) == users.end()) {
        cout << "User not found.\n";
        return;
    }
    cout << "Current balance for " << username << ": " << users[username].balance << "\n";
}

int main() {
    const string filename = "users.txt";

    loadUsersFromFile(filename);

    string choice;

    while (true) {
        cout << "\nSelect option:  1.register  2.login  3.transfer  4.balance  5.exit\n> ";
        cin >> choice;

        if (choice == "register") {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (registerUser(username, password)) {
                cout << "User registered.\n";
                users[username].balance = 100.0;
            }
            else {
                cout << "User already exists.\n";
            }

        }
        else if (choice == "login") {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (loginUser(username, password)) {
                cout << "Login successful.\n";
                cout << "Balance: " << users[username].balance << "\n";
            }
            else {
                cout << "Login failed.\n";
            }

        }
        else if (choice == "transfer") {
            string fromUser, toUser;
            double amount;

            cout << "Sender username: ";
            cin >> fromUser;
            cout << "Receiver username: ";
            cin >> toUser;
            cout << "Amount: ";
            cin >> amount;

            transfer(fromUser, toUser, amount);

        }
        else if (choice == "balance") {
            string username;
            cout << "Enter username: ";
            cin >> username;
            showBalance(username);

        }
        else if (choice == "exit") {
            saveUsersToFile(filename);
            cout << "Data saved. Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
