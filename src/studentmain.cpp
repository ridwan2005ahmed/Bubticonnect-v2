#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "src/function.h"
using namespace std;
#define nx '\n'

// Set text and background color
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

// Draw horizontal line with a single byte char
void drawLine(char ch = '=', int length = 60) {
    for (int i = 0; i < length; ++i) cout << ch;
    cout << nx;
}

// Set the entire console to white with black text
void setInitialConsoleStyle() {
    setColor(0, 15); // black text, white background
    system("cls");
}
/// Show important notice title


// Beautiful header
void name() {
    setColor(0, 15);
    drawLine('=', 60);
    cout << setw(40) << u8"📌  WELCOME TO BUBT I CONNECT" << nx;
    drawLine('=', 60);
    cout << nx;
    show_imp_notice();
    viewSideBySide();
}

// Menu screen
void showMenu() {
    name();
    setColor(1, 15); // blue text
    drawLine('-', 60);

    setColor(0, 15);
    cout << u8"🧭  What do you want to access today?" << nx << nx;

//    setColor(2, 15); cout << u8" 1. 🗺️  Smart RoadMap of varsity" << nx;
    setColor(3, 15); cout << u8" 2. 🧳 Lost and Found" << nx;
    setColor(4, 15); cout << u8" 3. 📝 Complaint Box" << nx;
    setColor(5, 15); cout << u8" 4. 📢 Notice" << nx;
    setColor(9, 15); cout << u8" 5. 🤖 Chat Bot" << nx;

    setColor(12, 15); cout << u8" 0. ❌ Exit" << nx;

    setColor(0, 15); // reset
    drawLine('-', 60);
}

// Wrong input handler
void wrongInput() {
    setColor(12, 15); // red text on white bg
    system("cls");
    drawLine('x', 60);
    cout << u8" ⚠️  Wrong Input! Please enter a correct number." << nx;
    drawLine('x', 60);
    setColor(0, 15);
}

int studentmain() {
    // Enable UTF-8 encoding in Windows console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    setInitialConsoleStyle(); // white background with black text

    int choice;
    do {
        
        showMenu();
        cout << u8"\n➡️  Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");

        switch (choice) {
            // case 1:
            //     maP();
            //     break;
            case 2:
                lostAndFound();
                break;
           
            case 3:
                complaint();
                break;
            case 4:
                notice();
                break;
            case 5:
                runChatbot();
                break;
            case 0:
                setColor(0, 15);
                cout << u8"👋 Exiting... Thank you for using Bubt I Connect!" << nx;
                break;
            default:
                wrongInput();
        }

        if (choice != 0) {
            cout << u8"\n➡️  Press Enter to continue...";
            cin.get();
            system("cls");
        }

    } while (choice != 0);

    return 0;
}


