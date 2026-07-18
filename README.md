# Advanced Console-Based ATM & Authentication System

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

A highly structured, interactive console application written in C that simulates a production-grade banking system. This repository features an advanced local user registration process, strict authentication workflows, core financial transaction operations, and dynamic, non-blocking console visual loading animations.

---

## 📋 Table of Contents
1. [Project Overview (#what)](#-project-overview-what)
2. [Context & Motivation (#where--why)](#-context--motivation-where--why)
3. [Key Features](#-key-features)
4. [Technical Deep Dive](#-technical-deep-dive)
5. [Architecture & Flow](#-architecture--flow)
6. [Installation & Compiling](#-installation--compiling)
7. [Author](#-author)

---

## 🔍 Project Overview (#what)
This application is a comprehensive simulation of an Automated Teller Machine (ATM) integrated with a modern terminal-based user registration and session management portal. Developed strictly in procedural C, it maps real-world financial transactions—such as multi-tier authentication validation, balance inquiry updates, safe capital withdrawal protection, and capital injection tracking—into a modular, lightweight terminal dashboard. 

The application utilizes native Windows architecture hooks to inject structured UI paradigms (like precise colored alerts and realistic multi-second background operational loading bars) into what is traditionally a static CLI environment.

---

## 🏛️ Context & Motivation (#where--why)

### Where Was It Developed?
This project was designed, engineered, and optimized within the academic context of the **Computer Programming Department at Bursa Uludağ University (Karacabey Vocational School)**. It serves as a benchmark utility showcasing advanced standalone runtime optimization, modular function separation, and precise command-line UI behavior.

### Why Was It Developed?
The structural logic behind this system aims to solve several foundational challenges in low-level systems programming:
*   **State Management:** Maintaining a persistent state of user profile fields (`struct`) during cross-functional pointer transitions (`&aktifKullanici`).
*   **UI/UX inside CLI:** Moving past static text feeds by deploying explicit console screen management tools (`system("cls")`), custom header dependencies (`renkler.h`), and timed terminal carriage resets (`
`).
*   **Buffer Control:** Managing runtime input stream security through validation checks on formatting parameters (`scanf` tracking) and forcing background buffers forward (`fflush(stdout)`) to simulate natural server-client operational delays.

---

## 🚀 Key Features

*   **Secure Multi-Field Registration:** Allows dynamic user sign-ups collecting Full Name, custom character Alphanumeric Passwords, and valid Gmail handles with a predefined baseline financial balance.
*   **Rigorous Input Verification:** Validates incoming user login metrics against structural instances using exact string comparisons (`strcmp`). 
*   **Complete ATM Service Menu:**
    *   **Withdrawal Protection:** Ensures transactions do not exceed current balances and blocks negative value injections.
    *   **Deposit Processing:** Computes instantaneous balance modifications with real-time value updates.
    *   **Balance Inquiries:** Securely fetches profile records behind a brief operational gateway screen.
*   **Dynamic UX Feedback Engines:** Replaces jarring terminal loops with smooth, multi-tiered visual loading screens (`.`, `..`, `...`) adjusting explicitly to distinct timing milestones using platform-specific asynchronous thread pauses.
*   **Color-Coded Diagnostic Reporting:** Leverages structural color alerts (Magenta for branding, Yellow for selections, Red for critical faults, and Green for successful transactions) to elevate readability.

---

## 🛠️ Technical Deep Dive

### 1. Data Structuring
All profile information is encapsulated tightly inside an independent data model block, ensuring clean parameter inheritance across operations:
```c
struct Kullanici {
    char isim[50];
    char sifre[50];
    char gmail[50];
    double bakiye;
};
```

### 2. High-Performance Buffer Management
To keep animations ticking naturally without graphical stuttering, the application directly bypasses standard lazy output buffers via forced flush pipelines:
```c
fflush(stdout);
printf("
"); // Dynamically resets the terminal cursor to line start
```

### 3. Native Platform Interoperability
The source code isolates platform routines, deploying target-specific headers (`windows.h`) to handle console device attributes safely:
```c
#ifdef _WIN32
void sleep_ms(int milliseconds) {
    Sleep(milliseconds);
}
#endif
```

---

## 🔀 Architecture & Flow

```
[ Application Boot ]
        │
        ▼
 ┌──────────────┐
 │ Registration │ ──► (Generates Struct Instance, Sets Default Balance)
 └──────────────┘
        │
        ▼
 ┌──────────────┐
 │ Login Portal │ ──► (Validates name & password via strcmp)
 └──────────────┘
        │
        ▼
 ┌──────────────────────────────────────────────┐
 │              Main ATM Core Menu              │
 ├───────────┬─────────────┬───────────┬────────┤
 │ 1. Withdraw│ 2. Deposit  │ 3. Balance│ 4. Exit│
 └───────────┴─────────────┴───────────┴────────┘
```

---

## 💻 Installation & Compiling

### Prerequisites
*   A valid C compiler configured on Windows (GCC / MinGW recommended).
*   A local dependency module for text coloring mapping (`renkler.h`) loaded inside your compiler include path.

### Build via Command Line
1. Clone this repository to your target workspace:
   ```bash
   git clone https://github.com/Kaanbuz123/Advanced-ATM-System.git
   cd Advanced-ATM-System
   ```
2. Compile using standard `gcc`:
   ```bash
   gcc main.c -o atm_system.exe
   ```
3. Run the compiled executable binary:
   ```bash
   ./atm_system.exe
   ```

---

## ✍️ Author

*   **Kaan Buz**
    *   *Academic Institution:* Bursa Uludağ University
    *   *Specialization Focus:* Computer Programming / Cyber Security Systems
    *   *GitHub Profile:* [Kaanbuz123](https://github.com/Kaanbuz123)

---
*Developed as a demonstration of procedural logic execution and CLI optimization principles.*
