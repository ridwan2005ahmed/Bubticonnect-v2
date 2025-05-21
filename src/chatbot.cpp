#include "function.h"                // Custom header file (assumed to contain function declarations)
#include <windows.h>                // For Windows-specific APIs (console color, system calls, etc.)
#include <bits/stdc++.h>
using namespace std;

// ======================
// Helper function to trim whitespace from both ends of a string
string trim(const string &s)
{
    size_t start = 0;
    //start < s.size() && 
    while (isspace(s[start])) start++;
    size_t end = s.size();
    while (end > start && isspace(s[end - 1])) end--;
    return s.substr(start, end - start);
}

// ======================
// Speak using Microsoft's speech synthesis
void speak(const string &phrase)
{
    //  = escapeDoubleQuotes(phrase);

    // PowerShell command to speak using Microsoft Zira voice
    string command = "powershell -Command \"Add-Type -AssemblyName System.Speech; "
                     "$speak = New-Object System.Speech.Synthesis.SpeechSynthesizer; "
                     "$speak.SelectVoice('Microsoft Zira Desktop'); "
                     "$speak.Volume = 90; "
                     "$speak.Rate = 0; "
                     "$speak.Speak(\\\"" + phrase + "\\\")\"";
    system(command.c_str());  // Execute the command
}

// ======================
// Load chat data from a file into a map
bool loadChatData(const string &filename, map<string, string> &chatData)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Failed to open chat data file: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        size_t delimPos = line.find('|');
        if (delimPos != string::npos)
        {
            string question = trim(line.substr(0, delimPos));
            string answer = trim(line.substr(delimPos + 1));
            transform(question.begin(), question.end(), question.begin(), ::tolower);
            chatData[question] = answer;  // Store in map
        }
    }
    file.close();
   return true;
}

// ======================
// Convert a string to lowercase
string toLower(const string &s)
{
    string copy = s;
    transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    return copy;
}

// ======================
// Split a string into words (ignores punctuation)
vector<string> splitIntoWords(const string &s)
{
    vector<string> words;
    string current;
    for (char c : s)
    {
        if (isalpha(c) || c == '\'') current += c;
        else if (!current.empty())
        {
            words.push_back(current);
            current.clear();
        }
    }
    if (!current.empty()) words.push_back(current);
    return words;
}

// ======================
// Levenshtein distance-based similarity percentage (edit distance)
int calculateSimilarity(const string &s1, const string &s2)
{
    const size_t len1 = s1.size(), len2 = s2.size();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

    for (size_t i = 0; i <= len1; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= len2; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= len1; ++i)
    {
        for (size_t j = 1; j <= len2; ++j)
        {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = min({dp[i - 1][j] + 1,
                            dp[i][j - 1] + 1,
                            dp[i - 1][j - 1] + cost});
        }
    }

    int maxLen = max(len1, len2);
    if (maxLen == 0) return 100;
    return 100 - (100 * dp[len1][len2]) / maxLen;
}

// ======================
// Get current system time in 12-hour format
string getCurrentTime()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char timeStr[50];
    strftime(timeStr, sizeof(timeStr), "%I:%M %p", ltm);
    return string(timeStr);
}

// ======================
// Get current date in full format
string getCurrentDate()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char dateStr[50];
    strftime(dateStr, sizeof(dateStr), "%A, %B %d, %Y", ltm);
    return string(dateStr);
}

// ======================
// Find best match for user's query
string findBestMatch(const string &userQuery, const map<string, string> &chatData)
{
    string query = toLower(trim(userQuery));

    // 1. Exact match
    auto exactMatch = chatData.find(query);
    if (exactMatch != chatData.end())
    {
        string response = exactMatch->second;
        // Handle dynamic tags for date/time
        size_t datePos = response.find("[DYNAMIC_DATE]");
        if (datePos != string::npos)
            response.replace(datePos, 14, getCurrentDate());

        size_t timePos = response.find("[DYNAMIC_TIME]");
        if (timePos != string::npos)
            response.replace(timePos, 14, getCurrentTime());

        return response;
    }

    // 2. Hardcoded emergency response
    if (query.find("first aid") != string::npos ||
        query.find("medical emergency") != string::npos ||
        query.find("emergency") != string::npos)
    {
        return "URGENT: Medical Center is on Ground floor, Admin Building. Emergency: 01723456780.";
    }

    // 3. Date/time fallback response
    if (query.find("date") != string::npos || query.find("today") != string::npos)
        return "Today's date is " + getCurrentDate();
    if (query.find("time") != string::npos || query.find("current time") != string::npos)
        return "The current time is " + getCurrentTime();

    // 4. Fuzzy match based on edit distance
    string bestMatch;
    int highestSimilarity = 0;
    const int SIMILARITY_THRESHOLD = 50;

    for (const auto &pair : chatData)
    {
        int similarity = calculateSimilarity(query, pair.first);
        if (similarity > highestSimilarity && similarity >= SIMILARITY_THRESHOLD)
        {
            highestSimilarity = similarity;
            bestMatch = pair.second;
        }
    }
    if (!bestMatch.empty()) return bestMatch;

    // 5. Partial word match fallback
    vector<string> queryWords = splitIntoWords(query);
    for (const auto &pair : chatData)
    {
        vector<string> keyWords = splitIntoWords(pair.first);

        for (const auto &qw : queryWords)
        {
            for (const auto &kw : keyWords)
            {
                if (qw == kw && kw.length() > 3)
                    return pair.second;
            }
        }

        if (query.find(pair.first) != string::npos || pair.first.find(query) != string::npos)
            return pair.second;
    }

    // Default fallback
    return "Sorry, I don't understand that. Please try another question.";
}

// ======================
// Main chatbot function
void runChatbot()
{
    system("cls");  // Clear console screen

    // Display welcome banner
    cout << "==========================" << endl;
    cout << "  Chatbot Bubt I Connect  " << endl;
    cout << "==========================" << endl << endl;

    // Load chat data from file
    map<string, string> chatData;
    if (!loadChatData("data/chatdata.txt", chatData))
    {
        cout << "Error loading chat data. Make sure 'chatdata.txt' exists." << endl;
        return;
    }

    // Initial greeting
    speak("Hello! I am your BUBT assistant. How can I help you today?");

    // Main loop
    while (true)
    {
        cout << "\nYou: ";
        string userInput;
        getline(cin, userInput);
        string query = toLower(trim(userInput));

        // Exit condition
        if (query == "exit" || query == "bye" || query == "stop")
        {
            cout << "Bubt I connect: Goodbye! Have a nice day!" << endl;
            speak("Goodbye! Have a nice day!");
            break;
        }

        // Predefined voice commands to open apps/websites
        if (query == "open youtube")
        {
            system("start https://www.youtube.com");
            cout << "Bubt I connect: Opening YouTube..." << endl;
            speak("Opening YouTube");
            continue;
        }
        if (query == "open facebook")
        {
            system("start https://www.facebook.com");
            cout << "Bubt I connect: Opening Facebook..." << endl;
            speak("Opening Facebook");
            continue;
        }
        if (query == "open google")
        {
            system("start https://www.google.com");
            cout << "Bubt I connect: Opening Google..." << endl;
            speak("Opening Google");
            continue;
        }
        if (query == "open codeforces")
        {
            system("start https://codeforces.com");
            cout << "Bubt I connect: Opening Codeforces..." << endl;
            speak("Opening Codeforces");
            continue;
        }
        if (query == "open notepad")
        {
            system("notepad.exe");
            cout << "Bubt I connect: Opening Notepad..." << endl;
            speak("Opening Notepad");
            continue;
        }
        if (query == "open calculator")
        {
            system("calc.exe");
            cout << "Bubt I connect: Opening Calculator..." << endl;
            speak("Opening Calculator");
            continue;
        }

        // Handle general questions
        string response = findBestMatch(query, chatData);
        cout << "Bubt I connect: " << response << endl;

            speak(response);
    }
}
