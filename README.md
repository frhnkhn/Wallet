# Wallet
# 💳 Digital Wallet System (C++)

## 📌 Overview

The **Digital Wallet System** is a console-based application developed using **C++** that simulates basic digital payment functionalities. The system allows users to create accounts, log in securely, manage wallet balances, and perform money transfers between users.

This project is implemented in a **single file (`main.cpp`)**, making it simple, lightweight, and easy to understand for beginners.

---

## 🚀 Features

* User Registration
* Secure Login (Mobile + PIN)
* Check Wallet Balance
* Add Money
* Send Money to Other Users
* Transaction Recording
* File-based Data Storage
* Menu-driven Interface

---

## 🧠 Concepts Used

* Object-Oriented Programming (OOP)
* Classes & Objects
* Encapsulation
* STL (vector)
* File Handling (`users.txt`)
* Menu-driven Programming

---

## 📁 Project Structure

```id="a8yq1k"
main.cpp        # Complete implementation
users.txt       # Stores user data
wallet          # Compiled executable (binary file)
```

---

## ⚙️ How to Run

### 🔧 Compile

```bash id="w0zjks"
g++ main.cpp -o wallet
```

### ▶️ Run

```bash id="m7qk3p"
./wallet
```

---

## 📖 How to Use

### 1️⃣ Register

* Select **Register**
* Enter name, mobile number, and PIN

### 2️⃣ Login

* Enter mobile number and PIN
* Access wallet menu

### 3️⃣ Wallet Menu Options

* **Balance** → View current balance
* **Add Money** → Add funds
* **Send Money** → Transfer money to another user
* **Transaction History** → View past transactions
* **Logout** → Return to main menu

---

## 📂 Data Storage

* `users.txt` → stores all user details
* (Transactions are stored in memory during runtime)

---

## ⚠️ Notes

* The `wallet` file is a **compiled binary**, not source code
* If VS Code shows *“file is not displayed…”*, that is normal
* Do not edit the `wallet` file

---

## ❗ Limitations

* Console-based (no GUI)
* Basic security (PIN only)
* No real payment integration
* Single-file implementation

---

## 🔮 Future Scope

* Add GUI (desktop or web)
* Store transactions in file
* Add admin panel
* Improve security (encryption, OTP)

---

## 👨‍💻 Author

Developed as part of an **Object-Oriented Programming project**.

---

## 📌 Note

This project is for **educational purposes only** and does not handle real financial transactions.
