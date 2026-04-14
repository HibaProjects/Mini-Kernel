
# Mini-Kernel (Unix Inspired)

##  Description
This project is a minimal 32-bit educational kernel written in C and Assembly.
It runs in QEMU and demonstrates basic OS concepts like booting, VGA output, and system structure.

---

## Features (Current Stage)

- Bootloader using Assembly (entry.asm)
- Kernel written in C
- VGA text output (screen driver)
- Basic system initialization
- Makefile build system
- Runs in QEMU emulator

---

##  Project Structure

boot/      -> bootloader code  
kernel/    -> main kernel logic  
drivers/   -> screen / keyboard drivers  
lib/       -> utility functions  
include/   -> header files  

---

## Requirements

Install dependencies:

```bash
sudo apt update
sudo apt install build-essential nasm qemu make gcc
