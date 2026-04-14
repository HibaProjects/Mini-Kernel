#include "screen.h"

/* port input */
static unsigned char inb(unsigned short port) {
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void kernel_main() {

    print_center("MiniKernel Ready");
    print("\nType something:\n");

    set_input_start(get_cursor_index());

    unsigned char shift = 0;
    unsigned char caps = 0;

    while (1) {

        unsigned char status = inb(0x64);
        if (!(status & 1))
            continue;

        unsigned char scancode = inb(0x60);

        /* SHIFT press */
        if (scancode == 0x2A || scancode == 0x36) {
            shift = 1;
            continue;
        }

        /* SHIFT release */
        if (scancode == 0xAA || scancode == 0xB6) {
            shift = 0;
            continue;
        }

        /* CAPS LOCK toggle */
        if (scancode == 0x3A) {
            caps = !caps;
            continue;
        }

        /* ignore key release */
        if (scancode & 0x80)
            continue;

        char c = 0;

        /* XOR logic */
        int upper = shift ^ caps;

        switch (scancode) {

            /* letters */
            case 0x1E: c = upper ? 'A' : 'a'; break;
            case 0x30: c = upper ? 'B' : 'b'; break;
            case 0x2E: c = upper ? 'C' : 'c'; break;
            case 0x20: c = upper ? 'D' : 'd'; break;
            case 0x12: c = upper ? 'E' : 'e'; break;
            case 0x21: c = upper ? 'F' : 'f'; break;
            case 0x22: c = upper ? 'G' : 'g'; break;
            case 0x23: c = upper ? 'H' : 'h'; break;
            case 0x17: c = upper ? 'I' : 'i'; break;
            case 0x24: c = upper ? 'J' : 'j'; break;
            case 0x25: c = upper ? 'K' : 'k'; break;
            case 0x26: c = upper ? 'L' : 'l'; break;
            case 0x32: c = upper ? 'M' : 'm'; break;
            case 0x31: c = upper ? 'N' : 'n'; break;
            case 0x18: c = upper ? 'O' : 'o'; break;
            case 0x19: c = upper ? 'P' : 'p'; break;
            case 0x10: c = upper ? 'Q' : 'q'; break;
            case 0x13: c = upper ? 'R' : 'r'; break;
            case 0x1F: c = upper ? 'S' : 's'; break;
            case 0x14: c = upper ? 'T' : 't'; break;
            case 0x16: c = upper ? 'U' : 'u'; break;
            case 0x2F: c = upper ? 'V' : 'v'; break;
            case 0x11: c = upper ? 'W' : 'w'; break;
            case 0x2D: c = upper ? 'X' : 'x'; break;
            case 0x15: c = upper ? 'Y' : 'y'; break;
            case 0x2C: c = upper ? 'Z' : 'z'; break;

            /* numbers + SHIFT symbols */
            case 0x02: c = shift ? '!' : '1'; break;
            case 0x03: c = shift ? '@' : '2'; break;
            case 0x04: c = shift ? '#' : '3'; break;
            case 0x05: c = shift ? '$' : '4'; break;
            case 0x06: c = shift ? '%' : '5'; break;
            case 0x07: c = shift ? '^' : '6'; break;
            case 0x08: c = shift ? '&' : '7'; break;
            case 0x09: c = shift ? '*' : '8'; break;
            case 0x0A: c = shift ? '(' : '9'; break;
            case 0x0B: c = shift ? ')' : '0'; break;

            /* symbols */
            case 0x0C: c = shift ? '_' : '-'; break;
            case 0x0D: c = shift ? '+' : '='; break;

            case 0x1A: c = shift ? '{' : '['; break;
            case 0x1B: c = shift ? '}' : ']'; break;

            case 0x27: c = shift ? ':' : ';'; break;
            case 0x28: c = shift ? '"' : '\''; break;

            case 0x33: c = shift ? '<' : ','; break;
            case 0x34: c = shift ? '>' : '.'; break;
            case 0x35: c = shift ? '?' : '/'; break;

            case 0x39: c = ' '; break;
            case 0x1C: c = '\n'; break;
            case 0x0E: c = '\b'; break;
        }

        if (c)
            print_char(c);
    }
}
