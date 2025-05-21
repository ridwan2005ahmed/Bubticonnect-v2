#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <limits>
#include <windows.h>
#include "function.h"

// #include <direct.h> // For _mkdir
using namespace std;

const int SHIFT = 200;

// Enable UTF-8 output in Windows Console
void enableUTF8()
{
    SetConsoleOutputCP(CP_UTF8);
}

// Password input masking
string inputPassword()
{
    string password;
    char ch;
    while ((ch = _getch()) != '\r')
    { // Until Enter is pressed
        if (ch == '\b')
        { // Backspace
            if (!password.empty())
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            cout << '*';
            password += ch;
        }
    }
    cout << endl;
    return password;
}

// Simple ASCII-shift encrypt
string encrypt(const string &password)
{
    string encrypted = password;
    for (char &ch : encrypted)
    {
        ch += SHIFT;
    }
    return encrypted;
}

// Simple ASCII-shift decrypt
string decrypt(const string &password)
{
    string decrypted = password;
    for (char &ch : decrypted)
    {
        ch -= SHIFT;
    }
    return decrypted;
}

// Dashboards
void studentDashboard(const string &username)
{
    cout << u8"\n🎓 Welcome, " << username << u8"! (Student Dashboard)\n";
}
void facultyDashboard(const string &username)
{
    cout << u8"\n👨‍🏫 Welcome, " << username << u8"! (Faculty Dashboard)\n";
}
void adminDashboard(const string &username)
{
    cout << u8"\n🛡️ Welcome, " << username << u8"! (Admin Dashboard)\n";
}

void registerUser()
{
    //_mkdir("data");

    string username, password, role;

    cout << u8"📄 Enter username: ";
    cin >> username;

    ifstream infile("data/users.txt");
    string line;
    while (getline(infile, line))
    {
        size_t p1 = line.find('|');
        if (p1 == string::npos)
            continue;
        string u = line.substr(0, p1);
        if (u == username)
        {
            cout << u8"⚠️ Username already exists!\n";
            infile.close();
            return;
        }
    }
    infile.close();

    cout << u8"🔒 Enter password: ";
    password = inputPassword();

    cout << u8"👥 Select role (student / faculty / admin): ";
    cin >> role;

    for (char &ch : role)
        ch = tolower(ch);
    if (role != "student" && role != "faculty" && role != "admin")
    {
        cout << u8"❌ Invalid role.\n";
        return;
    }

    string encryptedPass = encrypt(password);

    ofstream file("data/users.txt", ios::app);
    file << username << "|" << encryptedPass << "|" << role << endl;
    file.close();

    cout << u8"✅ Registered successfully!\n";
}

string role;
void login()
{
    string username, password;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    while (true)
    {
        system("cls");
        cout << u8"👤 Username: ";
        cin >> username;

        ifstream file("data/users.txt");
        string line, fileUser, filePass, fileRole;
        bool userExists = false;

        while (getline(file, line))
        {
            size_t p1 = line.find('|');
            size_t p2 = line.rfind('|');
            if (p1 == string::npos || p2 == string::npos || p1 == p2)
                continue;
            fileUser = line.substr(0, p1);
            if (fileUser == username)
            {
                filePass = line.substr(p1 + 1, p2 - p1 - 1);
                fileRole = line.substr(p2 + 1);
                fileRole = role;
                userExists = true;
                break;
            }
        }
        file.close();

        if (!userExists)
        {
            cout << u8"❌ Username not found! Redirecting to main menu...\n";
            Sleep(700);
            return; // Return to main menu
        }

        attempts = 0;
        while (attempts < MAX_ATTEMPTS)
        {
            system("cls");
            cout << u8"🔒 Password: ";
            password = inputPassword();
            string encryptedInput = encrypt(password);

            if (filePass == encryptedInput)
            {
                cout << u8"✅ Login successful!\n";
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
            }
            else
            {
                attempts++;
                cout << u8"❌ Wrong password. Attempts left: " << (MAX_ATTEMPTS - attempts) << "\n";
                Sleep(1500);

                if (attempts == MAX_ATTEMPTS)
                {
                    for (int i = 30; i >= 1; --i)
                    {
                        system("cls");
                        cout << u8"⏳ Too many failed attempts. Please wait: " << i << " seconds...\n";
                        Sleep(1000);
                    }
                    system("cls");
                }
            }
        }
    }
}

void displayMenu()
{
    cout << u8"==============================" << endl;
    cout << u8"   🎓 Welcome to BUBT iConnect" << endl;
    cout << u8"==============================" << endl;
    cout << u8"1. 🔐 Login" << endl;
    cout << u8"2. 📝 Register" << endl;
    cout << u8"3. ❌ Exit" << endl;
    cout << u8"------------------------------" << endl;
}

int main()
{
    enableUTF8();

    while (true)
    {
        displayMenu();

        int choice;
        cout << u8"Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");

        switch (choice)
        {
        case 1:
            login();
            if (role == "student")
                studentmain();
            else if (role == "faculty")
                facultyDashboard();
            else if (role == "admin")
                adminDashboard();

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