# Sahuji Cashier System

[![Apache License 2.0](https://img.shields.io/badge/License-Apache%202.0-red.svg)](https://www.apache.org/licenses/LICENSE-2.0)
[![GitHub Stars](https://img.shields.io/github/stars/Prarambha369/-SAHUJI-CASHIER.svg?style=social)](https://github.com/Prarambha369/-SAHUJI-CASHIER)
[![HackaTime](https://hackatime-badge.hackclub.com/U0894AG5K1C/-SAHUJI-CASHIER)](https://hackatime.hackclub.com/U0894AG5K1C)
---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Step-by-Step Usage Guide](#step-by-step-usage-guide)
- [Admin Functions](#admin-functions)
- [User Functions](#user-functions)
- [Changing Admin Password](#changing-admin-password)
- [Data Storage Update (2025)](#data-storage-update-2025)
- [Troubleshooting](#troubleshooting)
- [Screenshots and Videos](#screenshots-and-videos)
- [Contribution Guidelines](#contribution-guidelines)
- [License](#license)

---

## 🛒 Overview
**SAHUJI** is a console-based C++ application designed for small businesses to manage cashier operations. It helps you handle inventory, generate bills, manage customer data, and process credit cards, all from a simple terminal interface.

---

## ✨ Features
- **Product Management:** Add, edit, delete, and view products with details like price, quantity, tax, and discount.
- **Inventory Tracking:** Monitor stock levels and get alerts for low inventory.
- **Billing System:** Generate and view bills for purchases.
- **Customer Management:** Register customers, generate unique customer IDs, and track their purchases and points.
- **Admin Security:** Password-protected admin area with the ability to change the password.
- **Reports:** View product and billing reports.
- **Gift Hamper:** Identify and display the top customer of the year.
- **Cross-Platform:** Works on both Linux and Windows.

---

## 🚀 Step-by-Step Usage Guide

### 1. **Installation**
#### Linux
```sh
sudo apt install g++                # Install g++ if not already installed
g++ sahuji.cpp -o sahuji            # Compile the program (recompile after code changes)
./sahuji                            # Run the program
```
#### Windows
- Install a C++ compiler like MinGW or use Visual Studio.
- Compile with: `g++ sahuji.cpp -o sahuji`
- Run: `./sahuji` or `sahuji.exe` depending on your setup.

### 2. **Main Menu Navigation**
When you start the program, you'll see a menu with the following options:

1. **VIEW/GENERATE CUSTOMER ID**
2. **ADMIN**
3. **USER**
4. **EXIT**

Use the number keys to select an option and follow the on-screen prompts.

---

## 🔐 Admin Functions
To access admin features, select **ADMIN** from the main menu and enter the admin password (default: `admin`, or whatever you set).

**Admin Menu Options:**
1. Add product
2. View product details (by ID)
3. View all products
4. Edit product
5. Delete product
6. Refill product stock
7. View bills
8. Change Admin Password
9. Back to Main Menu

---

## 👤 User Functions
Select **USER** from the main menu to:
- View available products
- Purchase products (with or without a customer ID)
- Generate bills

---

## 🔑 Changing Admin Password
1. Log in as Admin.
   - **Note:** The Admin password is `admin` by default, and can be changed in the menu.
2. In the admin menu, select **8. Change Admin Password**.
3. Enter and confirm the new password.
4. The new password will be required for future admin logins.

---

## ⚡ Data Storage Update (2025)
- All data is now stored in plain text (CSV) files: `products.dat`, `customers.dat`, and `bills.dat`.
- If you previously used an old version, delete any existing `.dat` files before running the new version to avoid crashes.
- Data is cross-platform and human-readable.

---

## 🐞 Troubleshooting
- If you get a crash or see strange characters in `.dat` files, delete those files and re-add your data.
- Always recompile (`g++ sahuji.cpp -o sahuji`) after updating the code.

---

## 🖼️ Screenshots and Videos

- [Video](https://hc-cdn.hel1.your-objectstorage.com/s/v3/36e0dd2a5c46fef6a8141f9dc83062cd44e5cfa5_sahuji_app_run.mp4)

---

## 🤝 Contribution Guidelines
- Fork the repository.
- Make changes and submit a pull request.
- Ensure code is cross-platform compatible.
- Report issues on the GitHub page if available.

---

## 📄 License
This project is licensed under the [Apache License 2.0](LICENSE).

---

**Enjoy using Sahuji Cashier System! made with <3 by Praarmbha**
