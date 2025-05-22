#include <bits/stdc++.h>
#include "function.h"
#include <windows.h>
#include <cstdlib>

// Add declarations for setColor and drawLine if not already present in function.h
void setColor(int textColor, int bgColor);
void drawLine(char ch, int length);
using namespace std;
#define nx "\n"
void shownotice() {
    ifstream file("data/notice.txt");
    string line;

    cout << left << setw(50) << "Title"
         << "| " << left << setw(50) << "Description" << '\n';
    cout << string(105, '-') << '\n';

    while (getline(file, line)) {
        stringstream ss(line);
        string title, description;
        getline(ss, title, '|');
        getline(ss, description, '|');
        cout << left << setw(50) << title
             << "| " << left << setw(50) << description << '\n';
    }

    file.close();
}

void addnotice() {
    

    string title, describe;

    cout << "Title: " << nx;
    getline(cin, title);

    cout << "Describe: " << nx;
    getline(cin, describe);

    ofstream file("data/notice.txt", ios::app);
    if (file.is_open()) {
        file << title << "|" << describe << "\n";
        file.close();
        cout << "Everything Entered Successfully: " << title << endl;
    } else {
        cerr << "Failed to open notice file!" << endl;
    }
}




void show_imp_notice() {
    system("cls");
    ifstream file("data/notice.txt");
    string line;
 cout<< u8"📢 Important Notice"<<nx;
   // cout << left << setw(50) << "Title" << '\n';
    cout << string(105, '-') << '\n';

    while (getline(file, line)) {
        stringstream ss(line);
        string title;
        getline(ss, title, '|');
        
        cout << left << setw(50) << title<< '\n';
    }

    file.close();
       cout << string(105, '-') << '\n';
}
