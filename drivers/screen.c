#include "screen.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static int index = 0;
static int input_start = 0;

int get_cursor_index() {
    return index;
}

void set_input_start(int pos) {
    input_start = pos;
}

/* =========================
   SCROLL FUNCTION
   ========================= */
void scroll_screen() {

    char *video = (char*)0xB8000;

    /* move all rows up */
    for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
        video[i * 2]     = video[(i + VGA_WIDTH) * 2];
        video[i * 2 + 1] = video[(i + VGA_WIDTH) * 2 + 1];
    }

    /* clear last row */
    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x07;
    }

    index -= VGA_WIDTH;
    if (index < 0)
        index = 0;
}

/* =========================
   PRINT CHAR
   ========================= */
void print_char(char c) {

    char *video = (char*)0xB8000;

    /* SCROLL CHECK */
    if (index >= VGA_WIDTH * VGA_HEIGHT) {
        scroll_screen();
    }

    /* NEW LINE */
    if (c == '\n') {
        index += (VGA_WIDTH - (index % VGA_WIDTH));
        return;
    }

    /* BACKSPACE */
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

/* =========================
   PRINT STRING
   ========================= */
void print(const char *str) {
    for (int i = 0; str[i]; i++)
        print_char(str[i]);
}

/* =========================
   CENTER TEXT
   ========================= */
void print_center(const char *str) {

    int len = 0;
    while (str[len]) len++;

    int row = 12;
    int col = (VGA_WIDTH - len) / 2;

    char *video = (char*)0xB8000;

    for (int i = 0; i < len; i++) {
        int pos = (row * VGA_WIDTH + col + i) * 2;
        video[pos] = str[i];
        video[pos + 1] = 0x0A;
    }

    index = (row * VGA_WIDTH + col + len);
}
