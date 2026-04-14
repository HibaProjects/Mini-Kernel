Mini-Kernel (Unix Inspired OS)

Version: v1.0

Description

This project is a minimal 32-bit educational operating system kernel written in C and Assembly.

It runs in a simulated environment (QEMU) and demonstrates fundamental operating system concepts such as:

Boot process
Memory layout
VGA text mode output
Low-level system initialization
Features (Current Stage)

4.1 System Boot
Kernel boots successfully in QEMU
Displays welcome message:
Welcome to MiniKernel
Let's get started!

4.2 Screen Output
VGA text mode driver
Print strings to screen
Supports newline (\n)
Basic colored text output (green)

Project Structure

boot/ → Bootloader / entry point (Assembly)
kernel/ → Core kernel logic (C)
drivers/ → Screen, keyboard drivers
lib/ → Utility functions
include/ → Header files

Requirements

sudo apt update
sudo apt install build-essential nasm qemu gcc make

How to Compile

make

How to Run

make run

Example Output

Welcome to MiniKernel
Let's get started!

Git Flow
main → stable production version
develop → development branch
feature/* → new features
release/* → version preparation
hotfix/* → urgent fixes

Versioning
v1.0 → Boot + VGA output
v1.1 → Keyboard input (next step)
v2.0 → Mini shell system

Next Steps
Keyboard input handling
Real-time typing support
Mini shell (help, clear, echo, version)
Command interpreter

Author

Student Hiba Project - 2026 OS Development Challenge
