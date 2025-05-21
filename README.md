
# 💬 BUBT i-Connect – Virtual Campus Assistant

> 🤖 A smart terminal-based assistant system for students and faculty of **BUBT**  
> 🎓 Built with C++ | 💻 Voice-Powered | 🔍 Map Navigation | 📢 Notice & More

---

## 🧠 Overview

**BUBT i-Connect** is a C++ console application designed to improve student life on campus. It integrates an intelligent chatbot, room navigation map, notice board access, and more. With text-to-speech responses and smart query matching, this project demonstrates practical and innovative use of C++ beyond basic algorithms and data structures.

---

## 🚀 Key Features

### 🗣️ Chatbot Assistant
- Answers common university-related questions
- Responds using **Windows Speech Synthesizer (Microsoft Zira)**
- Handles dynamic queries like:
  - 📅 “What’s the date today?”
  - ⏰ “What’s the current time?”
  - 🚨 Emergency first aid information
- Supports fuzzy matching for better accuracy
- Special commands to open:
  - 🔹 YouTube, Facebook, Google
  - 🔹 Notepad, Calculator, Codeforces

---

### 🗺️ Smart Map Search
- Find faculty rooms or departments
- Case-insensitive search from `map.txt`
- Retry option if no match is found

---

### 📢 Notice Board
- Displays university notices stored in `notice.txt`

### 🧳 Lost & Found
- Submit or view lost/found items using `lostinfo.txt` and `findinfo.txt`

### 📝 Complaint Box
- File and store complaints via `complaint.txt`

---

## 🧑‍🤝‍🧑 Team Members

### 👨‍💻 Developers (Coders)
- **Ridwan Ahmed** –20244103146
- **Mazidur Rahman** – 20244103158
- **Shajidul Islam** – 20244103152

### 🧑‍🎓 Non-Coders (Data Collectors)
- **Snigdha Mim** – 20244103122
- **Rihab** – 20244103141
- **Mahir Shahriar Galib** – 20244103145

---

## 📁 Project Structure

```
📦 Bubticonnect
├── .vscode/                 # Optional: Editor settings
├── data/                    # Static files used by modules
│   ├── chatdata.txt         # Chatbot questions and answers
│   ├── complaint.txt        # Complaint submissions
│   ├── findinfo.txt         # Found item reports
│   ├── lostinfo.txt         # Lost item reports
│   ├── map.txt              # Faculty/room location info
│   └── notice.txt           # University notice content
├── src/                     # Core system source code
│   ├── chatbot.cpp          # Chatbot logic
│   ├── complaint.cpp        # Complaint module
│   ├── function.h           # Function declarations
│   ├── lostAndFound.cpp     # Lost & Found handling
│   ├── notice.cpp           # Notice system
│   ├── smartmap.cpp         # Smart room search
├── main.cpp                 # Main entry point
├── README.md                # 📘 Project documentation
├── a.exe                    # Windows executable (ignore this)
└── tempCodeRunnerFile.cpp   # Temporary file (delete this)
```

---

## 🛠️ How to Compile & Run

### 🧾 Prerequisites:
- Windows OS (Required for text-to-speech)
- C++ compiler (e.g. g++)

### 🔧 Compile
```bash
g++ src/*.cpp main.cpp -o a
```

### ▶️ Run
```bash
./a.exe
```

> ❗ Ensure the `data/` folder is present and properly populated with all `.txt` files.

---

## ✨ Future Enhancements
- ✅ GUI Version (using Qt or C++)
- ✅ Online Notice Sync via API
- ✅ Save chatbot learning history
- ✅ MySQL or SQLite database support

---

## 🏫 Project Info

🎓 **Project Name**: BUBT i-Connect  
🏢 **Institution**: Bangladesh University of Business & Technology (BUBT)  
📅 **Semester**: Spring 2025  
📘 **Course**: [software development project]  

---

## 🧑‍💻 Developed With ❤️ in C++

> “Technology should solve real problems — that’s what we aimed to do with **BUBT i-Connect**.”
