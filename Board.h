//
// Created by nikolay on 14.09.15.
//

#ifndef SNAKE_BOARD_H
#define SNAKE_BOARD_H

#include <stddef.h>

class Board {
public:
    enum block {
        FREE = 0,
        BLOCKED = 1,
        SNAKE = 2,
        APPLE = 3
    };

private:
    unsigned rows, cols;
    block **board;

    void copy(const Board &);

    void destroy();

public:
    Board(unsigned = 15, unsigned = 30, block ** = NULL);

    Board(const Board &);

    Board &operator=(const Board &);

    ~Board();

    bool is_free(unsigned x, unsigned y) const {
        return board[x][y] == FREE;
    }

    bool is_apple(unsigned x, unsigned y) const {
        return board[x][y] == APPLE;
    }

    bool is_blocked(unsigned x, unsigned y) const {
        return board[x][y] == BLOCKED;
    }

    void set_block(unsigned x, unsigned y, block b) {
        board[x][y] = b;
    }

    block get_block(unsigned x, unsigned y) const {
        return board[x][y];
    }

    unsigned get_rows() const {
        return rows;
    }

    unsigned get_cols() const {
        return cols;
    }

    void print_board() const;


};


#endif //SNAKE_BOARD_H
