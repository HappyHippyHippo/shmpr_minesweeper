#include <menu.h>

#include <hhh/hhh.h>

#include <stdio.h>

int menu_header(void)
{
    console_clear();
    printf("------------------------------------------------\n");
    printf("|   SUPER HIPER MEGA POWER RANGER MINESWEEPER  |\n");
    printf("------------------------------------------------\n");
    printf("\n");

    return ERROR_OK;
}

int menu_main(char* option)
{
    return console_read_option(option, "12340", "1 - Jogo facil\n"
                                                "2 - Jogo intermedio\n"
                                                "3 - Jogo dificil\n"
                                                "4 - Jogo adaptado\n"
                                                "\n"
                                                "0 - Sair\n\n>> ");
}

int menu_ask_board_width(int min, int max, int* response)
{
    return console_read_int_limit(response, min, max, "Qual a largura do tabuleiro ? (min = %d, max = %d)\n\n>> ", min, max);
}

int menu_ask_board_height(int min, int max, int* response)
{
    return console_read_int_limit(response, min, max, "Qual a altura do tabuleiro ? (min = %d, max = %d)\n\n>> ", min, max);
}

int menu_ask_board_mines(int min, int max, int* response)
{
    return console_read_int_limit(response, min, max, "Qual o número de minas ? (min = %d, max = %d)?\n\n>> ", min, max);
}

int menu_ask_action(char* option)
{
    return console_read_option(option, "1230", "1 - Abrir celula\n"
                                               "2 - Marcar mina\n"
                                               "3 - Remover marca de mina\n"
                                               "\n"
                                               "0 - Desistir\n\n>> ");
}

int menu_ask_cell_x(int min, int max, int* response)
{
    return console_read_int_limit(response, min, max, "Qual a coluna da celula ? (min = %d, max = %d)?\n\n>> ", min, max);
}

int menu_ask_cell_y(int min, int max, int* response)
{
    return console_read_int_limit(response, min, max, "Qual a linha da celula ? (min = %d, max = %d)?\n\n>> ", min, max);
}
