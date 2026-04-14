#include "screen.h"

static int index = 0;
static int input_start = 0;   

/* expose cursor position */
int get_cursor_index() {
    return index;
}

/* allow kernel to set start of input */
void set_input_start(int pos) {
    input_start = pos;
}

/* print character */
void print_char(char c) {

    char *video = (char*)0xB8000;

    /* NEW LINE */
    if (c == '\n') {
        index += (80 - (index % 80));
        return;
    }

    /* BACKSPACE (FIXED) */
    if (c == '\b') {
        if (index > input_start) {   
            index--;
            video[index * 2] = ' ';
            video[index * 2 + 1] = 0x07;
        }
        return;
    }

    video[index * 2] = c;
    video[index * 2 + 1] = 0x0A;
    index++;
}

/* print string */
void print(const char *str) {
    for (int i = 0; str[i]; i++)
        print_char(str[i]);
}

/* center text */
void print_center(const char *str) {
    int len = 0;
    while (str[len]) len++;

    int row = 12;
    int col = (80 - len) / 2;

    char *video = (char*)0xB8000;

    for (int i = 0; i < len; i++) {
        int pos = (row * 80 + col + i) * 2;
        video[pos] = str[i];
        video[pos + 1] = 0x0A;
    }

    index = (row * 80 + col + len);
}
