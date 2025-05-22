#include <iostream>
#include <windows.h>
#include <limits>
#include <cstdio>  // for remove()
#include "function.h"
using namespace std;

#define nx '\n'

void setColor(int textColor, int bgColor = 15) {  // default white background (15)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void wrongInput() {
    setColor(12, 15); // red text on white background
    system("cls");
    cout << u8" ⚠️ Wrong Input! Please enter a correct number." << nx;
    setColor(0, 15); // black text on white background
}

void showMenu() {
    setColor(0, 15); // black text, white background
    cout << u8"🧭 What do you want to access today?" << nx << nx;
    setColor(3, 15);
    cout << u8" 1. 📢 Notice" << nx;
    setColor(4, 15);
    cout << u8" 2. 🤖 Chat Bot" << nx;
    setColor(9, 15);
    cout << u8" 3. 🗨️ Live Chat" << nx;
    setColor(6, 15);
    cout << u8" 4. 🔓 Logout" << nx;
    setColor(12, 15);
    cout << u8" 0. ❌ Exit" << nx;
    setColor(0, 15);
}

int facultymain() {
    int choice;

    do {
        printBanner();
        showMenu();
        cout << u8"\n➡️ Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");

        switch (choice) {
            case 1:
                shownotice();
                break;
            case 2:
                runChatbot();
                break;
            case 3:
                livechatServer();
                break;
            case 4:
                cout << u8"🔓 Logging out...\n";
                remove("data/session.txt"); // Clear session on logout
                Sleep(1000);
                return 1; // signal to go back to login
            case 0:
                setColor(0, 15);
                cout << u8"👋 Exiting... Thank you for using Bubt I Connect!" << nx;
                Sleep(1000);
                exit(0);  // Immediately terminate the app
            default:
                wrongInput();
        }

        if (choice != 0 && choice != 4) {
            cout << u8"\n➡️ Press Enter to continue...";
            cin.get();
            system("cls");
        }
    } while (true);

    return 0;  // unreachable but required by function signature
}
