#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <limits>
#include <windows.h>
#include "src/function.h"

using namespace std;

const int SHIFT = 200;
string role;

// Set full white background and readable text
void setConsoleStyle() {
    system("color F0"); // Background: White (F), Text: Black (0)
}

// Enable UTF-8 output in Windows Console
void enableUTF8() {
    SetConsoleOutputCP(CP_UTF8);
}

// Password input masking
string inputPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            cout << '*';
            password += ch;
        }
    }
    cout << endl;
    return password;
}

// ASCII shift encryption
string encrypt(const string &password) {
    string encrypted = password;
    for (char &ch : encrypted) ch += SHIFT;
    return encrypted;
}

// ASCII shift decryption
string decrypt(const string &password) {
    string decrypted = password;
    for (char &ch : decrypted) ch -= SHIFT;
    return decrypted;
}

void studentDashboard(const string &username) {
    cout << u8"\n🎓 Welcome, " << username << u8"! (Student Dashboard)\n";
}

void facultyDashboard(const string &username) {
    facultymain(); // Moved logic into facultymain
}

void adminDashboard(const string &username) {
    cout << u8"\n🛡️ Welcome, " << username << u8"! (Admin Dashboard)\n";
}

// Check for active session
bool checkSession(string &username, string &userRole) {
    ifstream session("data/session.txt");
    if (session.is_open()) {
        getline(session, username);
        getline(session, userRole);
        session.close();
        return !username.empty() && !userRole.empty();
    }
    return false;
}

void saveSession(const string &username, const string &userRole) {
    ofstream session("data/session.txt", ios::trunc);
    session << username << '\n' << userRole;
    session.close();
}

void registerUser() {
    string username, password, userRole;

    cout << u8"📄 Enter username: ";
    cin >> username;

    ifstream infile("data/users.txt");
    string line;
    while (getline(infile, line)) {
        size_t p1 = line.find('|');
        if (p1 == string::npos) continue;
        string u = line.substr(0, p1);
        if (u == username) {
            cout << u8"⚠️ Username already exists!\n";
            infile.close();
            return;
        }
    }
    infile.close();

    cout << u8"🔒 Enter password: ";
    password = inputPassword();

    cout << u8"👥 Select role (student / faculty / admin): ";
    cin >> userRole;
    for (char &ch : userRole) ch = tolower(ch);

    if (userRole != "student" && userRole != "faculty" && userRole != "admin") {
        cout << u8"❌ Invalid role.\n";
        return;
    }

    string encryptedPass = encrypt(password);
    ofstream file("data/users.txt", ios::app);
    file << username << "|" << encryptedPass << "|" << userRole << endl;
    file.close();

    cout << u8"✅ Registered successfully!\n";
}

void login() {
    string username, password;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    while (true) {
        system("cls");
        cout << u8"👤 Username: ";
        cin >> username;

        ifstream file("data/users.txt");
        string line, fileUser, filePass, fileRole;
        bool userExists = false;

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            size_t p2 = line.rfind('|');
            if (p1 == string::npos || p2 == string::npos || p1 == p2) continue;
            fileUser = line.substr(0, p1);
            if (fileUser == username) {
                filePass = line.substr(p1 + 1, p2 - p1 - 1);
                fileRole = line.substr(p2 + 1);
                userExists = true;
                break;
            }
        }
        file.close();

        if (!userExists) {
            cout << u8"❌ Username not found! Redirecting to main menu...\n";
            Sleep(700);
            return;
        }

        attempts = 0;
        while (attempts < MAX_ATTEMPTS) {
            system("cls");
            cout << u8"🔒 Password: ";
            password = inputPassword();
            string encryptedInput = encrypt(password);

            if (filePass == encryptedInput) {
                cout << u8"✅ Login successful!\n";
                saveSession(username, fileRole);
                Sleep(1000);

                if (fileRole == "student")
                    studentDashboard(username);
                else if (fileRole == "faculty")
                    facultyDashboard(username);
                else if (fileRole == "admin")
                    adminDashboard(username);
                else
                    cout << u8"⚠️ Unknown role.\n";
                return;
            } else {
                attempts++;
                cout << u8"❌ Wrong password. Attempts left: " << (MAX_ATTEMPTS - attempts) << "\n";
                Sleep(1500);
                if (attempts == MAX_ATTEMPTS) {
                    for (int i = 30; i >= 1; --i) {
                        system("cls");
                        cout << u8"⏳ Too many failed attempts. Please wait: " << i << " seconds...\n";
                        Sleep(1000);
                    }
                }
            }
        }
    }
}

void displayMenu() {
    cout << u8"==============================" << endl;
    cout << u8"   🎓 Welcome to BUBT iConnect" << endl;
    cout << u8"==============================" << endl;
    cout << u8"1. 🔐 Login" << endl;
    cout << u8"2. 📝 Register" << endl;
    cout << u8"3. ❌ Exit" << endl;
    cout << u8"------------------------------" << endl;
}

int main() {
    enableUTF8();
    setConsoleStyle();

    string username, userRole;
    if (checkSession(username, userRole)) {
        cout << u8"🔓 Logged in as " << username << " (" << userRole << ")" << endl;
        Sleep(1500);
        system("cls");
        if (userRole == "student")
            studentDashboard(username);
        else if (userRole == "faculty")
            facultyDashboard(username);
        else if (userRole == "admin")
            adminDashboard(username);
        else
            cout << u8"⚠️ Unknown role in session!\n";
        return 0;
    }

    while (true) {
        displayMenu();

        int choice;
        cout << u8"Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                cout << u8"👋 Goodbye!\n";
                return 0;
            default:
                cout << u8"❌ Invalid choice!\n";
        }

        system("pause");
        system("cls");
    }

    return 0;
}
