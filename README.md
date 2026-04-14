# Mini-Kernel (Unix Inspired OS)

## Versioning

- v1.0 → Boot + VGA output (STABLE)
- v1.1 → Keyboard input (IN PROGRESS)
- v2.0 → Mini shell system (PLANNED)

---

## Description

This project is a minimal 32-bit educational operating system kernel written in C and Assembly.

It runs in a simulated environment (QEMU) and demonstrates fundamental operating system concepts such as:

- Boot process
- Memory layout
- VGA text mode output
- Low-level system initialization

---

## Features

### Boot System
- Kernel starts successfully in QEMU
- Displays welcome message

### Screen Output
- VGA text mode driver
- Print strings to screen
- Supports newline (\n)
- Basic colored text output (green)

---

## Project Structure

- boot/       → Bootloader / entry point (Assembly)
- kernel/     → Core kernel logic (C)
- drivers/    → Screen and keyboard drivers
- lib/        → Utility functions
- include/    → Header files

---

## Build & Run

### Install dependencies
```bash
sudo apt update
sudo apt install build-essential nasm qemu gcc make
```
### Build project
make clean

make
### Run in QEMU
make run
### Expected Output
Welcome to MiniKernel  
Let's get started!
### Git Flow

This project follows Git Flow methodology:

main → stable production version

develop → integration branch

feature/* → feature development

release/* → version preparation

hotfix/* → urgent fixes

### Version Plan

v1.0 → Boot + screen output

v1.1 → Keyboard input handling

v2.0 → Mini shell system (help, clear, echo, version)

### Next Steps

Keyboard input handling (v1.1) - 
Real-time typing support - 
Mini shell implementation:
help
clear
echo
version - 
Command interpreter loop
### Learning Outcomes

Understanding OS boot process

Low-level hardware interaction (VGA + keyboard)

Kernel development in C

Git Flow workflow

QEMU system emulation

### Author

Student Hiba Project – Mini Kernel (2026 OS Challenge)
