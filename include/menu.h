#ifndef MENU_H
#define MENU_H

int menu_header(void);

int menu_main(char* option);

int menu_ask_board_width(int min, int max, int* response);

int menu_ask_board_height(int min, int max, int* response);

int menu_ask_board_mines(int min, int max, int* response);

int menu_ask_action(char* option);

int menu_ask_cell_x(int min, int max, int* response);

int menu_ask_cell_y(int min, int max, int* response);

#endif
