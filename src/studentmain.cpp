#include <iostream>
#include <windows.h>
#include <limits>
#include <cstdio> // for remove()
#include "function.h"
using namespace std;

#define nx '\n'

void setsColor(int textColor, int bgColor = 15)
{ // default white background (15)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void wrongsInput()
{
    setsColor(12, 15); // red text on white background
    system("cls");
    cout << u8" ⚠️ Wrong Input! Please enter a correct number." << nx;
    setsColor(0, 15); // black text on white background
}

void showsMenu()
{
    setsColor(0, 15);
    cout << u8"🧭  What do you want to access today?" << nx << nx;
    setsColor(3, 15);
    cout << u8" 1. 🧳 Lost and Found" << nx;
    setsColor(4, 15);
    cout << u8" 2. 📝 Add Complaint" << nx;
    setsColor(5, 15);
    cout << u8" 3. 📢 Notice" << nx;
    setsColor(9, 15);
    cout << u8" 4. 🤖 Chat Bot" << nx;
    setsColor(2, 15);
    cout << u8" 5. 🗺️ Live Chat" << nx;
    setsColor(6, 15);
    cout << u8" 6. 🔓 Logout" << nx;
    setsColor(12, 15);
    cout << u8" 0. ❌ Exit" << nx;
}

int studentmain()
{
    int choice;

    do
    {
        printBanner();
        show_imp_notice();
        viewSideBySide();

        showsMenu();

        cout << u8"\n➡️ Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");

        switch (choice)
        {
        case 1:
            lostAndFound();
            break;
        case 2:
            addcomplaint();
            break;
        case 3:
            shownotice();
            break;
        case 4:
            runChatbot();
            break;
        case 5:
            clientmain();
            break;
        case 6:
            cout << u8"🔓 Logging out...\n";
            remove("data/session.txt"); // Clear session on logout
            Sleep(1000);
            return 1; // signal to go back to login
        case 0:
            setsColor(0, 15);
            cout << u8"👋 Exiting... Thank you for using Bubt I Connect!" << nx;
            Sleep(1000);
            exit(0); // Immediately terminate the app
        default:
            wrongsInput();
        }

        if (choice != 0 && choice != 4)
        {
            cout << u8"\n➡️ Press Enter to continue...";
            cin.get();
            system("cls");
        }
    } while (true);

    return 0; // unreachable but required by function signature
}
