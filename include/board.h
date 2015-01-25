#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>

/**
 * @brief Minesweeper board
 */
typedef struct Board Board;

/**
 * @brief Board creation
 *
 * @param width
 * @param height
 * @param n_mines
 * @return
 */
Board* board_create(size_t width, size_t height, size_t n_mines);

/**
 * @brief Board destruction
 *
 * @param board
 * @return
 */
int board_destroy(Board** board);

/**
 * @brief Board cell mine flag
 *
 * @param board
 * @param x
 * @param y
 * @return
 */
int board_flag_cell_on(Board* board, size_t x, size_t y);

/**
 * @brief Board cell mine flag
 *
 * @param board
 * @param x
 * @param y
 * @return
 */
int board_flag_cell_off(Board* board, size_t x, size_t y);

/**
 * @brief Board cell show
 *
 * @param board
 * @param x
 * @param y
 * @param is_mine
 * @return
 */
int board_open_cell(Board* board, size_t x, size_t y, int* is_mine);

/**
 * @brief Board cell visible state
 *
 * @param board
 * @param x
 * @param y
 * @param is_open
 * @return
 */
int board_is_cell_open(Board* board, size_t x, size_t y, int* is_open);

/**
 * @brief Board completion check
 *
 * @param board
 * @param x
 * @param y
 * @param is_complete
 * @return
 */
int board_is_complete(Board* board, int* is_complete);

/**
 * @brief Board console presentation
 *
 * @param board
 * @param show
 * @return
 */
int board_print(Board* board, int show);

#endif
