# Time-Locked File Locker (C)

A command-line file access control utility written in C that allows files to be locked using a password and a time limit.  
While locked, files cannot be accessed or modified directly and must be handled through the program.

---

## Overview

This project provides controlled access to files by combining:
- Password-based authentication
- Time-based locking
- Persistent metadata storage using a binary file

It is designed for scenarios where files need to be temporarily protected and accessed only under specific conditions.

---

## Features

- Lock existing files using a password
- Time-based access control (in minutes)
- Support for multiple locked files
- Persistent storage using a binary vault file
- Password attempt limiting
- Emergency override mechanism
- Controlled file access (view, edit, re-lock, delete)
- Safe removal of locked files and records

---

## How It Works

1. A text file must already exist before it can be locked. ( create one if not available ) 
2. When a file is locked:
   - The original file is encrypted and renamed with a `.locked` extension
   - File metadata is stored in a binary file (`vault.dat`)
3. To access a file:
   - The user provides the filename and password
   - The program checks password attempts and lock time
4. Files can only be accessed, edited, or deleted through the program.

---

## Project Structure
- timefile/
- |--main.c //Menu , layout 
- |--locker.c //Core logic for lock , unlock , edit and delete
- |--vault.h //headerfile to store structure and functions
- |--README.md

files generated at runtime : 
- 'vault.dat'
- '.locked'
- '.exe' ( executable file ) 

to compile : gcc main.c locker.c -o lockfile.exe

## Menu Options
  1. Create Vault – Lock a file using password and time duration
  2. Access Vault – Unlock and manage a locked file
  3. Delete Vault – Remove a locked file and its record
  4. Edit File – Temporarily decrypt, edit, and re-lock a file
  5. Exit

## Limitations
  1. Uses XOR-based encryption (not intended for high-security applications)
  2. Filenames with spaces are not supported
  3. Password input is visible in the terminal
  4. Designed for local file access control

## Author 
Ronak Sarda
github : https://github.com/ronaksarda
