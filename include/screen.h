#ifndef SCREEN_H
#define SCREEN_H

void print(const char *str);
void print_char(char c);
void print_center(const char *str);

int get_cursor_index();     
void set_input_start(int pos);   

#endif
