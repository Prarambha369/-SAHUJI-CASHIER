# Sahuji Cashier System

[![Apache License 2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://www.apache.org/licenses/LICENSE-2.0)

## Table of Contents
- [What is this?](#what-is-this)
- [How it helps](#how-it-helps)
- [How to use](#how-to-use)

## What is this?
SAHUJI is a console-based C++ application designed for a cashier system. It manages inventory, generates bills, handles customer data, and processes credit cards.

## How it helps
This system automates retail operations like adding products, calculating taxes and discounts, tracking stock levels, and generating reports, which reduces errors and improves efficiency for small businesses.

## How to use
- **Platform Dependency:** Requires Windows OS due to use of Windows-specific libraries (e.g., <windows.h>). It will not run on Linux without modifications.
- **Prerequisites:** A C++ compiler such as MinGW or Visual Studio.
- **Steps:**
  1. Compile the code using `g++ sahuji.cpp -o sahuji` in a command prompt.
  2. Run the executable with `./sahuji`.
  3. Use the menu options for admin or user functions to manage the system.

**Note:** Ensure proper file permissions for data storage files like 'itemstore.dat'.
