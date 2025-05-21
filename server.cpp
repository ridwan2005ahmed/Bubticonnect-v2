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

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printMessage(const string& sender, const string& msg, int color) {
    setColor(color);
    cout << sender << ": " << msg << endl;
    setColor(COLOR_RESET);
}

void clearInputLine() {
    cout << "\r                                                  \r";
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    sockaddr_in server_addr, client_addr;
    char buffer[1024];
    string inputBuffer;
    string lastSent = "";  // To track last message sent

    printMessage("System", "Initializing Winsock...", COLOR_SYSTEM);
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printMessage("System", "WSAStartup failed: " + to_string(WSAGetLastError()), COLOR_SYSTEM);
        return 1;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printMessage("System", "Could not create socket: " + to_string(WSAGetLastError()), COLOR_SYSTEM);
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printMessage("System", "Bind failed: " + to_string(WSAGetLastError()), COLOR_SYSTEM);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    listen(server_socket, 1);
    printMessage("System", "Waiting for client to connect...", COLOR_SYSTEM);

    int client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == INVALID_SOCKET) {
        printMessage("System", "Accept failed: " + to_string(WSAGetLastError()), COLOR_SYSTEM);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printMessage("System", "Client connected! Start chatting.\nType 'exit' to quit.", COLOR_SYSTEM);

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
                printMessage("Client", received, COLOR_THEIRS);
                setColor(COLOR_YOU);
                cout << "You> " << inputBuffer;
                setColor(COLOR_RESET);
            }
        } else if (bytesReceived == 0) {
            printMessage("System", "Client disconnected.", COLOR_SYSTEM);
            break;
        } else {
            int err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK) {
                printMessage("System", "recv failed: " + to_string(err), COLOR_SYSTEM);
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
                    printMessage("You", inputBuffer, COLOR_YOU);
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

    printMessage("System", "Server shutting down.", COLOR_SYSTEM);
    return 0;
}
