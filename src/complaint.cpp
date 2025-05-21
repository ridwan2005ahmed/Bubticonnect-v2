#include <bits/stdc++.h>
#include <conio.h> 
#include <windows.h> 
using namespace std;
#define nx "\n"

void complaint();

string inputPassword();
int option;
void addcomplaint();
void showcomplaint();

void complaint() {
    do {
        cout << "1.Add Complaint" << nx;
        cout << "2.Show Complaint" << nx;
        cout << "0. Back to Main Menu\n"; 
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        system("cls"); // clear screen after each selection

        switch (option) {
        case 1:
            addcomplaint();
            break;
        case 2:
            showcomplaint();
            break;
        case 0:
            cout << "Returning to main menu..." << nx;
            break;
        default:
            cout << "--------------------Wrong input--------------------" << nx;
            cout << "----------Please enter the correct number----------" << nx;
        }

        if (option != 0) {
            cout << "\nPress Enter to continue...";
            cin.get(); // Wait for Enter
            system("cls");
        }
    } while (option != 0);
}

string encrypt(string data) {
    for (auto &ch : data) {
        ch += 200;
    }
    return data;
}

string decrypt(string data) {
    for (auto &ch : data) {
        ch -= 200;
    }
    return data;
}

void addcomplaint() {
    string title, describe;

    cout << "Title: " << nx;
    getline(cin, title);

    cout << "Describe your complaint: " << nx;
    getline(cin, describe);

    title = encrypt(title);
    describe = encrypt(describe);

    ofstream file("data/complaint.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << title << "|" << describe << "\n";
        file.close();
        cout << "Everything Entered Successfully: " << title << endl;
    }
}

void showcomplaint() {
    string pass = "1234";
    string password;
    int attempts = 0;
    const int maxAttempts = 3;

    while (attempts < maxAttempts) {
        cout << "Enter Password: ";
        password = inputPassword();
        system("cls");

        if (password == pass) {
            break;  // Correct password
        } else {
            attempts++;
            if (attempts < maxAttempts) {
                cout << "Wrong Password (" << attempts << "/" << maxAttempts << ")\n";
            }
        }
    }

    if (attempts == maxAttempts) {

        for (int i = 30; i >= 1; --i) {
            cout << "\rToo many failed attempts. Please wait " << i << " seconds... ";
            Sleep(1000); // wait for 1 second
            
        }
        system("cls");
        return;  // Exit without showing complaints
    }

    // Password was correct – show complaints
    ifstream file("data/complaint.txt");
    string line;
    cout << left << setw(50) << "Title"
         << "| " << left << setw(50) << "Description" << '\n';
    cout << string(105, '-') << '\n';

    while (getline(file, line)) {
        stringstream ss(line);
        string title, description;
        getline(ss, title, '|');
        getline(ss, description, '|');
        title = decrypt(title);
        description = decrypt(description);
        cout << left << setw(50) << title
             << "| " << left << setw(50) << description << '\n';
    }

    file.close();
}

string inputPassword() {
    string password;
    char ch;

    while (true) {
        ch = getch();  // read character without echoing

        if (ch == '\r') {  // Enter key
            cout << endl;
            break;
        } else if (ch == '\b') {  // Backspace
            if (!password.empty()) {
                password.pop_back();
                // Erase last '*'
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';  // show asterisk for each character
        }
    }

    return password;
}
