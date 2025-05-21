// lostAndFound.cpp
#include <bits/stdc++.h>
#include "function.h"
#include <fstream>
using namespace std;
#define nx '\n'
void addLostInfo();
void addFindInfo(); 
void lostAndFound()
{
    int option;
    do
    {
        cout << "\n--- Lost and Found ---\n";
        cout << "1. Add Lost Item\n";
        cout << "2. Add Found Item\n";
        cout << "0. Back to Main Menu\n"; // Added option 0 to go back
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        system("cls"); // clear screen after each selection

        switch (option)
        {
        case 1:
            addLostInfo();
            break;
        case 2:
        addFindInfo();
            break;

        case 0:
            cout << "Returning to main menu..." << nx;
            break;
        default:
            cout << "--------------------Wrong input--------------------" << nx;
            cout << "----------Please enter the correct number----------" << nx;
        }

        if (option != 0)
        {
            cout << "\nPress Enter to continue...";
            cin.get(); // Wait for Enter
              system("cls");
        }

    } while (option != 0);
}
void addLostInfo()
{
    string name, contact, details;

    cout << "Enter lost item info (name): ";
    getline(cin, name);

    cout << "Enter contact Number: ";
    getline(cin, contact); 

    cout << "Enter Details: ";
    getline(cin, details);

    ofstream file("data/lostinfo.txt", ios::out | ios::app);
    if (file.is_open())
    {
        file << name << "|" << contact << "|" << details << "\n";
        file.close();
        cout << "Everything Entered Successfully: " << name << endl;
    }
 
}


void addFindInfo(){
    string name, contact, details;

    cout << "Enter Found item info (name): ";
    getline(cin, name);

    cout << "Enter contact Number: ";
    getline(cin, contact); 

    cout << "Enter Details: ";
    getline(cin, details);

    ofstream file("data/findinfo.txt", ios::out | ios::app);
    if (file.is_open())
    {
        file << name << "|" << contact << "|" << details << "\n";
        file.close();
        cout << "Everything Entered Successfully: " << name << endl;
    }
  
}


void viewSideBySide() {
    ifstream lostFile("data/lostinfo.txt");
    ifstream foundFile("data/findinfo.txt");  // ✅ Corrected filename

    if (!lostFile.is_open() || !foundFile.is_open()) {
        cerr << "Error: Could not open one or both files.\n";
        return;
    }

    cout << left << setw(50) << "Lost Items"
         << "| " << left << setw(50) << "Found Items" << '\n';
    cout << string(105, '-') << '\n';

    string lostLine, foundLine;
    while (true) {
        string lostText = "", foundText = "";

        if (getline(lostFile, lostLine)) {
            stringstream ss(lostLine);
            string name, contact, details;
            getline(ss, name, '|');
            getline(ss, contact, '|');
            getline(ss, details, '|');
            lostText = name + " - " + contact + " - " + details;
        }

        if (getline(foundFile, foundLine)) {
            stringstream ss(foundLine);
            string name, contact, details;
            getline(ss, name, '|');
            getline(ss, contact, '|');
            getline(ss, details, '|');
            foundText = name + " - " + contact + " - " + details;
        }

        if (lostText.empty() && foundText.empty()) break;

        cout << left << setw(50) << lostText
             << "| " << left << setw(50) << foundText << '\n';
    }

    lostFile.close();
    foundFile.close();
}




