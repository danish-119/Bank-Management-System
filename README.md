# Bank Management System

## Description

This project is a **Bank Management System** implemented in **C language**, developed as a **Semester Project** for the Programming Fundamentals course (CSC-103) at Comsats University Islamabad-Lahore Campus.

> **Note:** This is a student project for educational purposes only. It is **not a real banking system** and should not be used for actual financial transactions.

The system demonstrates basic banking operations and programming concepts, including file handling, struct usage, and menu-driven applications.

---

## Project Overview

The Bank Management System allows users to simulate essential banking tasks, such as account creation, login, money deposit/withdrawal, money transfer, and viewing transaction history. It also includes an admin section to manage accounts for demonstration purposes.

The system emphasizes:

* **Educational Value:** Teaches file handling, menu-driven interfaces, and account management in C.
* **Simulation:** All operations are performed on CSV files and do not involve real money.
* **User Interaction:** Provides an interactive console menu for navigating and performing tasks.

---

## Features

### Admin Section

* **Admin Login:** Restricted access using a fixed PIN for demonstration purposes.
* **View All Accounts:** Lists all accounts stored in the system.
* **View Transaction History:** Shows simulated transaction records.
* **Suspend Accounts:** Demonstrates account suspension by removing account data.

### Account Management

* **Account Creation:** Users can create simulated bank accounts with unique numbers and passwords.
* **Account Login:** Secure login simulation.
* **Account Information:** View details of a simulated account.
* **Account Deletion:** Permanently remove a simulated account.

### Balance and Transactions

* **Deposit Money:** Add simulated funds to the account.
* **Withdraw Money:** Withdraw simulated funds with certain restrictions.
* **Money Transfer:** Transfer funds between simulated accounts.
* **Transaction History:** Maintains a record of all simulated transactions.

### User Assistance

* **Help & Feedback:** Provides instructions and guidance for using the project.
* **Credit Section:** Displays project information, version, and author details.

---

## Usage

1. **Compile and Run:** Use a C compiler to run `BankManagementSystem.c`.
2. **Navigate Menus:** Use `W` (up) and `S` (down) keys to navigate, `Enter` to select, and `Esc` to return to previous menus.
3. **Simulated Account Operations:** Create accounts, perform deposits, withdrawals, and transfers—all simulated.
4. **Admin Access:** Log in using the admin PIN to view or manage simulated accounts.

---

## Technical Details

* **Language:** C
* **Storage:** Uses CSV files (`Accounts Information.Csv` and `Transactions.Csv`) to simulate persistent storage.
* **Password Security:** 4-digit numeric passwords (for simulation only).
* **Transaction Rules:** Withdrawal limited to 65% of the balance and must be in multiples of 500 (simulated rules).

---
