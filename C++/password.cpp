#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string generatePassword(int length) {
    string lower = "abcdefghijklmnopqrstuvwxyz";
    string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string digits = "0123456789";
    string symbols = "!@#$%^&*()-_+=<>?";

    string all = lower + upper + digits + symbols;
    string password = "";

    srand(time(0)); 

    for (int i = 0; i < length; ++i) {
        int index = rand() % all.size();
        password += all[index];
    }

    return password;
}

int main() {
    int length;
    cout << "Enter desired password length: ";
    cin >> length;

    if (length < 6) {
        cout << "Password too short. Try at least 6 characters.\n";
        return 1;
    }

    string newPass = generatePassword(length);
    cout << "Generated password: " << newPass << "\n";

    return 0;
}
