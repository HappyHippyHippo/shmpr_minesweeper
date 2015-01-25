#include "board.h"

#include <hhh/hhh.h>

#include <stdio.h>
#include <time.h>

#define board_get_cell(board, x, y) ((board)->cells[y * (board)->width + x])

#define board_cell_is_mine(cell) (((cell) >> 24) & 0xff)
#define board_cell_is_visible(cell) (((cell) >> 16) & 0xff)
#define board_cell_is_flagged(cell) (((cell) >> 8) & 0xff)
#define board_cell_get_adjacency(cell) ((cell) & 0xff)

#define board_cell_set(empty, visible, flagged, adjacency) ((((empty) & 0xff) << 24) | (((visible) & 0xff) << 16) | (((flagged) & 0xff) << 8) | ((adjacency) & 0xff))
#define board_cell_set_mine(cell) (board_cell_set(1, board_cell_is_visible(cell), board_cell_is_flagged(cell), board_cell_get_adjacency(cell)))
#define board_cell_set_visible(cell) (board_cell_set(board_cell_is_mine(cell), 1, board_cell_is_flagged(cell), board_cell_get_adjacency(cell)))
#define board_cell_set_flag_on(cell) (board_cell_set(board_cell_is_mine(cell), board_cell_is_visible(cell), 1, board_cell_get_adjacency(cell)))
#define board_cell_set_flag_off(cell) (board_cell_set(board_cell_is_mine(cell), board_cell_is_visible(cell), 0, board_cell_get_adjacency(cell)))
#define board_cell_add_adjacency(cell) (board_cell_set(board_cell_is_mine(cell), board_cell_is_visible(cell), board_cell_is_flagged(cell), board_cell_get_adjacency(cell) + 1))

#define xor_swap(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct Board
{
    size_t width;
    size_t height;
    size_t n_mines;
    size_t n_open;

    unsigned int* cells;
};

Board* board_create(size_t width, size_t height, size_t n_mines)
{
    Board* board = NULL;
    unsigned int* mines, i, random, size = width * height, cell;
    int x, y, x_adj, y_adj;

    // argument check
    if (width == 0 || height == 0 || n_mines == 0 || n_mines >= width * height)
        return NULL;

    // alloc memory
    if ((board = malloc(sizeof(Board))) == NULL)
        return NULL;

    // alloc memory
    if ((board->cells = calloc(size, sizeof(unsigned int))) == NULL)
    {
        free(board);

        return NULL;
    }

    // board parameter initialization
    board->width = width;
    board->height = height;
    board->n_mines = n_mines;
    board->n_open = 0;

    // mine position array allocation
    if ((mines = malloc(sizeof(unsigned int) * size)) == NULL)
    {
        free(board->cells);
        free(board);

        return NULL;
    }

    // mines position array initialization
    for (i = 0; i < size; ++i)
        mines[i] = i;

    // mines position randomization
    srand(time(NULL));
    for (i = 0; i < size - 1; ++i)
    {
        random = rand() % (size - i - 1) + i;
        if (random != i)
            xor_swap(mines[random], mines[i]);
    }

    // mines allocation on the board
    for (i = 0; i < board->n_mines; ++i)
    {
        x = mines[i] % board->width;
        y = mines[i] / board->width;

        cell = board_get_cell(board, x, y);
        board_get_cell(board, x, y) = board_cell_set_mine(cell);

        // add adjacency values
        for (y_adj = max((int) y - 1, 0); y_adj <= min((int) y + 1, (int) height - 1); ++y_adj)
        {
            for (x_adj = max((int) x - 1, 0); x_adj <= min((int) x + 1, (int) width - 1); ++x_adj)
            {
                cell = board_get_cell(board, x_adj, y_adj);
                board_get_cell(board, x_adj, y_adj) = board_cell_add_adjacency(cell);
            }
        }
    }

    // release mines position array memory
    free(mines);

    return board;
}

int board_destroy(Board** board)
{
    // argument check
    if (board == NULL || *board == NULL)
        return ERROR_INVALID_ARGUMENT;

    // release memory
    free((*board)->cells);
    free(*board);
    *board = NULL;

    return ERROR_OK;
}

int board_flag_cell_on(Board* board, size_t x, size_t y)
{
    unsigned int cell;

    // argument check
    if (board == NULL)
        return ERROR_INVALID_ARGUMENT;

    // argument check
    if (x >= board->width || y >= board->height)
        return ERROR_INVALID_INDEX;

    // flag the cell as having a mine
    cell = board_get_cell(board, x, y);
    board_get_cell(board, x, y) = board_cell_set_flag_on(cell);

    return ERROR_OK;
}

int board_flag_cell_off(Board* board, size_t x, size_t y)
{
    unsigned int cell;

    // argument check
    if (board == NULL)
        return ERROR_INVALID_ARGUMENT;

    // argument check
    if (x >= board->width || y >= board->height)
        return ERROR_INVALID_INDEX;

    // remove the mine flag
    cell = board_get_cell(board, x, y);
    board_get_cell(board, x, y) = board_cell_set_flag_off(cell);

    return ERROR_OK;
}

int board_open_cell(Board* board, size_t x, size_t y, int* is_mine)
{
    unsigned int cell;
    int x_adj, y_adj, aux_is_mine;

    // argument check
    if (board == NULL || is_mine == NULL)
        return ERROR_INVALID_ARGUMENT;

    // argument check
    if (x >= board->width || y >= board->height)
        return ERROR_INVALID_INDEX;

    cell = board_get_cell(board, x, y);

    // check if cell is already visible or is flagged as a mine
    if (board_cell_is_visible(cell) || board_cell_is_flagged(cell))
        return ERROR_INVALID_INDEX;

    // retrieve if the cell is a mine
    *is_mine = board_cell_is_mine(cell);
    if (!board_cell_is_mine(cell))
        ++board->n_open;

    // flag the cell as visible
    board_get_cell(board, x, y) = board_cell_set_visible(cell);

    // check if is to open adjacencies
    if (!board_cell_is_mine(cell) && board_cell_get_adjacency(cell) == 0)
    {
        for (y_adj = max((int) y - 1, 0); y_adj <= min((int) y + 1, (int) board->height - 1); ++y_adj)
        {
            for (x_adj = max((int) x - 1, 0); x_adj <= min((int) x + 1, (int) board->width - 1); ++x_adj)
            {
                // open adjacent cell
                board_open_cell(board, x_adj, y_adj, &aux_is_mine);
            }
        }
    }

    return ERROR_OK;
}

int board_is_cell_open(Board* board, size_t x, size_t y, int* is_open)
{
    unsigned int cell;

    // argument check
    if (board == NULL || is_open == NULL)
        return ERROR_INVALID_ARGUMENT;

    // argument check
    if (x >= board->width || y >= board->height)
        return ERROR_INVALID_INDEX;

    // retrieve the cell visible flag value
    cell = board_get_cell(board, x, y);
    *is_open = board_cell_is_visible(cell);

    return ERROR_OK;
}

int board_is_complete(Board* board, int* is_complete)
{
    // argument check
    if (board == NULL)
        return ERROR_INVALID_ARGUMENT;

    // check if the board is fully opened
    *is_complete = board->n_open + board->n_mines == board->width * board->height;

    return ERROR_OK;
}

int board_print(Board* board, int show)
{
    int row, col;
    unsigned int cell, adjacency;

    // argument check
    if (board == NULL)
        return ERROR_INVALID_ARGUMENT;

    // print rows indexes
    printf("\t");
    for (row = 0; row < board->width; ++row)
    {
        printf("%3d", row);
    }
    printf("\n");

    printf("\t");
    for (row = 0; row < board->width; ++row)
    {
        printf("---");
    }
    printf("\n");

    // print board
    for (row = 0; row < board->height; ++row)
    {
        printf("\t");
        for (col = 0; col < board->width; ++col)
        {
            // check if the cell is to be presented
            cell = board_get_cell(board, col, row);
            if (show || board_cell_is_visible(cell))
            {
                // check if the cell is a mine
                if (board_cell_is_mine(cell))
                {
                    // check if the cell is flagged
                    if (board_cell_is_flagged(cell))
                        printf("%3c", 'P');
                    else
                        printf("%3c", 'X');
                }
                else
                {
                    // check if is to present the adjacency number os an empty space
                    adjacency = board_cell_get_adjacency(cell);
                    if (adjacency != 0)
                        printf("%3d", board_cell_get_adjacency(cell));
                    else
                        printf("   ");
                }
            }
            else
            {
                // check if the cell is flagged
                if (board_cell_is_flagged(cell))
                    printf("%3c", 'P');
                else
                    printf("%3c", '.');
            }
        }

        // print row index
        printf("| %3d", row);
        printf("\n");
    }
    printf("\n");

    return ERROR_OK;
}
