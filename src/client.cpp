#include <iostream>
#include <winsock2.h>
#include <string>
#include <conio.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

// Color codes
#define COLOR_YOU 10      // Green
#define COLOR_THEIRS 11   // Cyan
#define COLOR_SYSTEM 12   // Red
#define COLOR_RESET 7     // Default

// Constants
const int BUFFER_SIZE = 4096;
const int PORT = 8080;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printMessage(const string& sender, const string& msg, int color) {
    setColor(color);
    cout << sender << ": " << msg << endl;
    setColor(COLOR_RESET);
}

void clearScreen() {
    system("cls");
}

void displayWelcome() {
    setColor(COLOR_SYSTEM);
    cout << "=== Simple Chat Client ===" << endl;
    cout << "Commands:" << endl;
    cout << "/exit - Quit the program" << endl;
    cout << "/clear - Clear the screen" << endl;
    setColor(COLOR_RESET);
    cout << endl;
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    sockaddr_in server;
    char buffer[BUFFER_SIZE];
    string inputBuffer;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "WSAStartup failed: " << WSAGetLastError() << endl;
        return 1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cerr << "Could not create socket: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    // Get server IP
    string ip;
    setColor(COLOR_SYSTEM);
    cout << "Enter server IP (default 127.0.0.1): ";
    setColor(COLOR_RESET);
    getline(cin, ip);
    if (ip.empty()) ip = "127.0.0.1";

    // Configure server address
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Connect to server
    setColor(COLOR_SYSTEM);
    cout << "Connecting to " << ip << "..." << endl;
    setColor(COLOR_RESET);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        cerr << "Connection failed: " << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Set non-blocking mode
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    // Clear screen and show welcome message
    clearScreen();
    displayWelcome();
    printMessage("System", "Connected to server!", COLOR_SYSTEM);

    // Initial input prompt
    setColor(COLOR_YOU);
    cout << "You> ";
    setColor(COLOR_RESET);

    while (true) {
        // Receive messages from server
        int bytesReceived = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';

            // Clear current input line
            cout << "\r                                                  \r";

            // Print server message
            printMessage("Server", buffer, COLOR_THEIRS);

            // Reprint input prompt and restore buffer
            setColor(COLOR_YOU);
            cout << "You> " << inputBuffer;
            setColor(COLOR_RESET);
        }
        else if (bytesReceived == 0) {
            printMessage("System", "Server disconnected", COLOR_SYSTEM);
            break;
        }

        // Handle user input
        if (_kbhit()) {
            char ch = _getch();

            // Backspace
            if (ch == '\b') {
                if (!inputBuffer.empty()) {
                    inputBuffer.pop_back();
                    cout << "\b \b";
                }
            }
            // Enter
            else if (ch == '\r') {
                // Clear input line
                cout << "\r                                                  \r";

                if (!inputBuffer.empty()) {
                    if (inputBuffer == "/exit") {
                        send(sock, "/exit", 5, 0);
                        break;
                    }
                    else if (inputBuffer == "/clear") {
                        clearScreen();
                        displayWelcome();
                    }
                    else {
                        send(sock, inputBuffer.c_str(), (int)inputBuffer.size(), 0);
                        printMessage("You", inputBuffer, COLOR_YOU);
                    }
                    inputBuffer.clear();
                }

                // Reprint prompt
                setColor(COLOR_YOU);
                cout << "You> ";
                setColor(COLOR_RESET);
            }
            // Printable characters
            else if (ch >= 32 && ch <= 126) {
                inputBuffer += ch;
                setColor(COLOR_YOU);
                cout << ch;
                setColor(COLOR_RESET);
            }
        }

        Sleep(50);
    }

    // Cleanup
    closesocket(sock);
    WSACleanup();
    printMessage("System", "Connection closed", COLOR_SYSTEM);
    return 0;
}
