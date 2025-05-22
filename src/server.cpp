#include <bits/stdc++.h>
#include <winsock2.h>
#include <conio.h>
#include <windows.h>
#include "function.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;



// Color codes
#define COLOR_YOU 1    // Dark Blue
#define COLOR_THEIRS 2 // Dark Green
#define COLOR_SYSTEM 4 // Dark Red
#define COLOR_RESET 0  // Default

void setColor(int textColor) {
    // White background = 15 (0xF)
    // Shift background color 4 bits left, OR with textColor
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15 << 4) | textColor);
}

void printserverMessage(const string& sender, const string& msg, int color) {
    setColor(color);
    cout << sender << ": " << msg << endl;
    setColor(COLOR_RESET);
}

void clearInputLine() {
    cout << "\r                                                  \r";
}

void livechatServer() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    sockaddr_in server_addr, client_addr;
    char buffer[1024];
    string inputBuffer;
    string lastSent = "";  // To track last message sent

    printserverMessage("System", "Initializing Winsock...", COLOR_SYSTEM);
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printserverMessage("System", "WSAStartup failed: " + to_string(WSAGetLastError()), COLOR_SYSTEM);
        return ;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printserverMessage("System", "Could not create socket: " + to_string(WSAGetLastError()), COLOR_SYSTEM);
        WSACleanup();
        return ;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printserverMessage("System", "Bind failed: " + to_string(WSAGetLastError()), COLOR_SYSTEM);
        closesocket(server_socket);
        WSACleanup();
        return ;
    }

    listen(server_socket, 1);
    printserverMessage("System", "Waiting for client to connect...", COLOR_SYSTEM);

    int client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == INVALID_SOCKET) {
        printserverMessage("System", "Accept failed: " + to_string(WSAGetLastError()), COLOR_SYSTEM);
        closesocket(server_socket);
        WSACleanup();
        return ;
    }

    printserverMessage("System", "Client connected! Start chatting.\nType 'exit' to quit.", COLOR_SYSTEM);

    // Set non-blocking mode
    u_long mode = 1;
    ioctlsocket(client_socket, FIONBIO, &mode);

    setColor(COLOR_YOU);
    cout << "You> ";
    setColor(COLOR_RESET);

    while (true) {
        // Receive message from client
        int bytesReceived = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            string received = buffer;

            if (received != lastSent) { // Prevent echo
                clearInputLine();
                printserverMessage("Client", received, COLOR_THEIRS);
                setColor(COLOR_YOU);
                cout << "You> " << inputBuffer;
                setColor(COLOR_RESET);
            }
        } else if (bytesReceived == 0) {
            printserverMessage("System", "Client disconnected.", COLOR_SYSTEM);
            break;
        } else {
            int err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK) {
                printserverMessage("System", "recv failed: " + to_string(err), COLOR_SYSTEM);
                break;
            }
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
                clearInputLine();

                if (!inputBuffer.empty()) {
                    if (inputBuffer == "exit") break;
                    send(client_socket, inputBuffer.c_str(), (int)inputBuffer.size(), 0);
                    printserverMessage("You", inputBuffer, COLOR_YOU);
                    lastSent = inputBuffer;
                    inputBuffer.clear();
                }

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

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    printserverMessage("System", "Server shutting down.", COLOR_SYSTEM);
    return ;
}
