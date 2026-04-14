#include "screen.h"

#define VIDEO_MEMORY (char*)0xB8000
#define GREEN 0x02

void putstr(const char *str) {
    char *video = VIDEO_MEMORY;
    int row = 0, col = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\n') {
            row++;
            col = 0;
        } else {
            int offset = (row * 80 + col) * 2;
            video[offset] = str[i];
            video[offset + 1] = GREEN;
            col++;
        }
        i++;
    }
}

void putstr_center(const char *str) {
    char *video = VIDEO_MEMORY;

    int row = 12;
    int i = 0;

    while (str[i] != '\0') {
        int start = i;
        int len = 0;

        while (str[i + len] != '\0' && str[i + len] != '\n') {
            len++;
        }

        int col = (80 - len) / 2;

        for (int j = 0; j < len; j++) {
            int offset = (row * 80 + col + j) * 2;
            video[offset] = str[start + j];
            video[offset + 1] = GREEN;
        }

        i += len;

        if (str[i] == '\n') {
            row++;
            i++;
        }
    }
}
