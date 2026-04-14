#include "keyboard.h"
#include "screen.h"

#define KEYBOARD_PORT 0x60

static unsigned char inb(unsigned short port) {
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static char keymap[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0',
    '-', '=', '\b',
    'q','w','e','r','t','y','u','i','o','p',
    '[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';',
    '\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/'
};

void keyboard_handler() {
    unsigned char scancode = inb(KEYBOARD_PORT);

    if (scancode & 0x80)
        return;

    char c = keymap[scancode];

    if (c)
        print_char(c);
}
