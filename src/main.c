#include <stdlib.h>

#include <board.h>
#include <menu.h>

#include <hhh/hhh.h>

#define BOARD_MIN_WIDTH  5
#define BOARD_MAX_WIDTH  30
#define BOARD_MIN_HEIGHT 5
#define BOARD_MAX_HEIGHT 30

#define BOARD_EASY_WIDTH_FRAC     3.0
#define BOARD_EASY_HEIGHT_FRAC    3.0
#define BOARD_EASY_MINES_FRAC     10

#define BOARD_MEDIUM_WIDTH_FRAC   (3.0 / 2.0)
#define BOARD_MEDIUM_HEIGHT_FRAC  (3.0 / 2.0)
#define BOARD_MEDIUM_MINES_FRAC   8

#define BOARD_HARD_WIDTH_FRAC     1.0
#define BOARD_HARD_HEIGHT_FRAC    1.0
#define BOARD_HARD_MINES_FRAC     5

int main(void)
{
    char option;
    int width, height, mines;

    Board* board = NULL;
    int x, y, is_mine, play, is_complete;

    do
    {
        menu_header();
        menu_main(&option);
        switch (option)
        {
        case '1':
            {
                width  = BOARD_MAX_WIDTH  / BOARD_EASY_WIDTH_FRAC;
                height = BOARD_MAX_HEIGHT / BOARD_EASY_HEIGHT_FRAC;
                mines  = width * height   / BOARD_EASY_MINES_FRAC;
            }
            break;
        case '2':
            {
                width  = BOARD_MAX_WIDTH  / BOARD_MEDIUM_WIDTH_FRAC;
                height = BOARD_MAX_HEIGHT / BOARD_MEDIUM_HEIGHT_FRAC;
                mines  = width * height   / BOARD_MEDIUM_MINES_FRAC;
            }
            break;
        case '3':
            {
                width  = BOARD_MAX_WIDTH  / BOARD_HARD_WIDTH_FRAC;
                height = BOARD_MAX_HEIGHT / BOARD_HARD_HEIGHT_FRAC;
                mines  = width * height   / BOARD_HARD_MINES_FRAC;
            }
            break;
        case '4':
            {
                menu_header();
                menu_ask_board_width(BOARD_MIN_WIDTH, BOARD_MAX_WIDTH, &width);
                menu_ask_board_height(BOARD_MIN_HEIGHT, BOARD_MAX_HEIGHT, &height);
                menu_ask_board_mines(1, (width * height) / BOARD_HARD_MINES_FRAC, &mines);
            }
            break;
        }

        switch (option)
        {
        case '1':
        case '2':
        case '3':
        case '4':
            {
                board = board_create(width, height, mines);
                play = 1;

                do
                {
                    menu_header();
                    board_print(board, 0);
                    menu_ask_action(&option);

                    switch (option)
                    {
                    case '1':
                        {
                            menu_header();
                            board_print(board, 0);
                            menu_ask_cell_x(0, width - 1, &x);
                            menu_ask_cell_y(0, height - 1, &y);

                            if (board_open_cell(board, x, y, &is_mine) == 0)
                            {
                                menu_header();
                                board_print(board, 0);

                                if (is_mine)
                                {
                                    play = 0;

                                    console_read_enter("A celula %dx%d era uma mina ... PERDEU ... (carrege no ENTER para continuar)", x, y);
                                }
                                else
                                {
                                    board_is_complete(board, &is_complete);
                                    if (is_complete)
                                    {
                                        play = 0;

                                        console_read_enter("Todas as minas descobertas ... GANHOU !!! (carrege no ENTER para continuar)");
                                    }
                                }
                            }
                        }
                        break;
                    case '2':
                        {
                            menu_header();
                            board_print(board, 0);
                            menu_ask_cell_x(0, width - 1, &x);
                            menu_ask_cell_y(0, height - 1, &y);

                            board_flag_cell_on(board, x, y);
                        }
                        break;
                    case '3':
                        {
                            menu_header();
                            board_print(board, 0);
                            menu_ask_cell_x(0, width - 1, &x);
                            menu_ask_cell_y(0, height - 1, &y);

                            board_flag_cell_off(board, x, y);
                        }
                        break;
                    case '0':
                        {
                            play = 0;

                            console_read_enter("Bem, fica para a proxima ... (carrege no ENTER para continuar)");
                        }
                        break;
                    }

                } while (play);

                board_destroy(&board);
            }

            option = '1';
            break;
        }
    } while (option != '0');

    return 0;
}
