#include "idt.h"

void idt_init() {
    // For now: just enable interrupts
    __asm__ volatile ("cli");
    __asm__ volatile ("sti");
}
