ASM = nasm
CC = gcc
LD = ld

CFLAGS = -m32 -ffreestanding -fno-pie -fno-pic -Iinclude
LDFLAGS = -m elf_i386 -nostdlib -T linker.ld

all: kernel.elf

entry.o:
	$(ASM) -f elf32 boot/entry.asm -o entry.o

kernel.o:
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o

screen.o:
	$(CC) $(CFLAGS) -c drivers/screen.c -o screen.o

keyboard.o:
	$(CC) $(CFLAGS) -c drivers/keyboard.c -o keyboard.o

idt.o:
	$(CC) $(CFLAGS) -c drivers/idt.c -o idt.o

kernel.elf: entry.o kernel.o screen.o keyboard.o idt.o
	$(LD) $(LDFLAGS) entry.o kernel.o screen.o keyboard.o idt.o -o kernel.elf

run:
	qemu-system-i386 -kernel kernel.elf

clean:
	rm -f *.o *.elf
