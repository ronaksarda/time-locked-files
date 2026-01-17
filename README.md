# Time-Locked File Locker

A C-based command-line program that restricts access to a file until a specified time using a password.

This project was built as an early independent exercise to understand file handling, time-based constraints, and basic access control through implementation.

---

## Why This Project Exists

Most operating systems do not provide simple user-level mechanisms to restrict file access based on time.

This project explores how such a constraint can be implemented in software by combining:
- System time
- File handling
- Basic password-based access checks

The goal was learning through building rather than creating a production-ready security tool.

---

## What It Does

- Allows a user to lock a file with:
  - A password
  - A future unlock time
- Prevents access to the file until the specified time is reached
- Allows access only after successful password verification and time validation

---

## How It Works (High Level)

1. The user selects a file to lock
2. A password and unlock time are set
3. Until the unlock time is reached:
   - File access is restricted
4. After the unlock time:
   - The correct password allows access

Internally, the program relies on system time checks and file handling logic to enforce these rules.

---

## Installation

Clone the repository and compile the source files:

```bash
git clone https://github.com/ronaksarda/time-locked-files.git
cd time-locked-files
gcc main.c locker.c -o time_lock
.\time_lock

```
## Use Cases

Restricting access to personal files until a future date

Enforcing self-imposed time-based access rules

Practicing constraint-based logic and file handling in C

## File structure 

- The project is organized into multiple source files separating the main program flow and core locking logic.

- The exact structure may change as the project evolves.

## Limitations

- This project is intended for learning purposes only

- Password handling is basic and not secure by modern standards

- File access control is implemented at the program level, not the OS level

- Not suitable for production or real security use

## What I Learned

- Working with system time in C

- Handling files and enforcing access rules

- Translating real-world constraints into program logic

- Understanding how small design decisions affect correctness

## Future Improvements

- Encrypting locked files

- Improving password handling

- Better error handling and user feedback

- Cross-platform compatibility

# Author : Ronak Sarda 
