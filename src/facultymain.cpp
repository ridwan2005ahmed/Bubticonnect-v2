#include <bits/stdc++.h>
#include "function.h"
#include <windows.h>
using namespace std;
#define nx '\n'
void setColor(int textColor, int bgColor)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void wrongInput()
{
  setColor(12, 15); // red text on white bg
  system("cls");
  cout << u8" ⚠️  Wrong Input! Please enter a correct number." << nx;
  setColor(0, 15);
}


void showMenu()
{

  setColor(0, 15);
  cout << u8"🧭  What do you want to access today?" << nx << nx;
  setColor(3, 15);
  cout << u8" 1.  📢 Notice" << nx;
  setColor(4, 15);
  cout << u8" 2.🤖 Chat Bot " << nx;
  setColor(9, 15);
  cout << u8" 3.🗨️ live chat" << nx;
  setColor(12, 15);
  cout << u8" 0. ❌ Exit" << nx;
  setColor(0, 15); // reset
}
int facultymain()
{
  {

    int choice;
    do
    {
      showMenu();
      cout << u8"\n➡️  Enter your choice: ";
      cin >> choice;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      system("cls");

      switch (choice)
      {
      case 1:
        shownotice();
        break;
      case 2:
        runChatbot();
        break;

      case 3:
        livechatServer();
        break;
      case 0:
        setColor(0, 15);
        cout << u8"👋 Exiting... Thank you for using Bubt I Connect!" << nx;
        break;
      default:
        wrongInput();
      }

      if (choice != 0)
      {
        cout << u8"\n➡️  Press Enter to continue...";
        cin.get();
        system("cls");
      }

    } while (choice != 0);

    return 0;
  }
}