#include "screen.h"
#include "string.h"

static unsigned char inb(unsigned short port) {
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

/* =========================
   VGA CURSOR CONTROL
   ========================= */
static void move_cursor(unsigned short pos) {
    __asm__ volatile("outb %0, %1" : : "a"((unsigned char)(pos >> 8)), "Nd"(0x3D4));
    __asm__ volatile("outb %0, %1" : : "a"((unsigned char)(pos & 0xFF)), "Nd"(0x3D5));
}

/* =========================
   SHELL BUFFER
   ========================= */
static char buffer[128];
static int len = 0;
static int cursor = 0;

/* =========================
   KEYBOARD STATE
   ========================= */
static int shift_pressed = 0;
static int caps_lock = 0;

/* =========================
   CLEAR BUFFER
   ========================= */
void clear_buffer() {
    for (int i = 0; i < 128; i++)
        buffer[i] = 0;

    len = 0;
    cursor = 0;
}

/* =========================
   PROMPT
   ========================= */
void print_prompt() {
    print("\nminiHibaKernel> ");
}

/* =========================
   COMMANDS
   ========================= */
void cmd_help() {
    print("\nhelp - show commands");
    print("\nclear - clear screen");
    print("\nversion - show version");
    print("\necho - print text");
}

void cmd_version() {
    print("\nMiniKernel v1.2 (Boucle Infinie)");
}

void cmd_clear() {
    unsigned short *video = (unsigned short *)0xB8000;

    for (int i = 0; i < 80 * 25; i++)
        video[i] = (0x0F << 8) | ' ';

    move_cursor(0);
}

void cmd_echo(char *cmd) {
    print("\n");
    print(cmd + 5);
}

/* =========================
   EXECUTOR
   ========================= */
void execute_command(char *cmd) {

    if (cmd[0] == 0)
        return;
    if (strcmp(cmd, "help") == 0) cmd_help();
    else if (cmd[0]=='c') cmd_clear();
    else if (cmd[0]=='v') cmd_version();
    else if (cmd[0]=='e') cmd_echo(cmd);
    else print("\nUnknown command");
}

/* =========================
   KERNEL MAIN
   ========================= */
void kernel_main() {

    print_center("MiniKernel v1.4");
    print("\nCursor + Shift + CapsLock");

    print_prompt();

    while (1) {

        unsigned char status = inb(0x64);
        if (!(status & 1))
            continue;

        unsigned char scancode = inb(0x60);

        /* =========================
           SHIFT + CAPS HANDLING
           ========================= */

        /* SHIFT press */
        if (scancode == 0x2A || scancode == 0x36) {
            shift_pressed = 1;
            continue;
        }

        /* SHIFT release */
        if (scancode == 0xAA || scancode == 0xB6) {
            shift_pressed = 0;
            continue;
        }

        /* CAPS LOCK toggle */
        if (scancode == 0x3A) {
            caps_lock = !caps_lock;
            continue;
        }

        /* =========================
           ARROW KEYS
           ========================= */
        if (scancode == 0x4B) { // LEFT
            if (cursor > 0) {
                cursor--;
                move_cursor(cursor + 80);
            }
            continue;
        }

        if (scancode == 0x4D) { // RIGHT
            if (cursor < len) {
                cursor++;
                move_cursor(cursor + 80);
            }
            continue;
        }

        /* ignore key release */
        if (scancode & 0x80)
            continue;

        char c = 0;

        switch (scancode) {

            /* letters */
            case 0x1E: c = 'a'; break;
            case 0x30: c = 'b'; break;
            case 0x2E: c = 'c'; break;
            case 0x20: c = 'd'; break;
            case 0x12: c = 'e'; break;
            case 0x21: c = 'f'; break;
            case 0x22: c = 'g'; break;
            case 0x23: c = 'h'; break;
            case 0x17: c = 'i'; break;
            case 0x24: c = 'j'; break;
            case 0x25: c = 'k'; break;
            case 0x26: c = 'l'; break;
            case 0x32: c = 'm'; break;
            case 0x31: c = 'n'; break;
            case 0x18: c = 'o'; break;
            case 0x19: c = 'p'; break;
            case 0x10: c = 'q'; break;
            case 0x13: c = 'r'; break;
            case 0x1F: c = 's'; break;
            case 0x14: c = 't'; break;
            case 0x16: c = 'u'; break;
            case 0x2F: c = 'v'; break;
            case 0x11: c = 'w'; break;
            case 0x2D: c = 'x'; break;
            case 0x15: c = 'y'; break;
            case 0x2C: c = 'z'; break;

            /* numbers */
            case 0x02: c = '1'; break;
            case 0x03: c = '2'; break;
            case 0x04: c = '3'; break;
            case 0x05: c = '4'; break;
            case 0x06: c = '5'; break;
            case 0x07: c = '6'; break;
            case 0x08: c = '7'; break;
            case 0x09: c = '8'; break;
            case 0x0A: c = '9'; break;
            case 0x0B: c = '0'; break;

            case 0x39: c = ' '; break;
            case 0x1C: c = '\n'; break;
            case 0x0E: c = '\b'; break;
        }

        if (!c)
            continue;

        /* =========================
           APPLY SHIFT / CAPS
           ========================= */

        /* letters */
        if (c >= 'a' && c <= 'z') {
            if ((shift_pressed && !caps_lock) || (!shift_pressed && caps_lock)) {
                c = c - 32;
            }
        }

        /* numbers → symbols when shift */
        if (shift_pressed) {
            switch (c) {
                case '1': c = '!'; break;
                case '2': c = '@'; break;
                case '3': c = '#'; break;
                case '4': c = '$'; break;
                case '5': c = '%'; break;
                case '6': c = '^'; break;
                case '7': c = '&'; break;
                case '8': c = '*'; break;
                case '9': c = '('; break;
                case '0': c = ')'; break;
            }
        }

        /* =========================
           ENTER
           ========================= */
        if (c == '\n') {

            buffer[len] = 0;

            print("\n");
            execute_command(buffer);

            clear_buffer();
            print_prompt();
        }

        /* =========================
           BACKSPACE
           ========================= */
        else if (c == '\b') {

            if (cursor > 0) {

                cursor--;
                len--;

                for (int i = cursor; i < len; i++)
                    buffer[i] = buffer[i + 1];

                print_char('\b');
            }
        }

        /* =========================
           INSERT CHAR
           ========================= */
        else {

            for (int i = len; i > cursor; i--)
                buffer[i] = buffer[i - 1];

            buffer[cursor] = c;

            cursor++;
            len++;

            print_char(c);
        }
    }
}
