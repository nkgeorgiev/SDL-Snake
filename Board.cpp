//
// Created by nikolay on 14.09.15.
//

#include <cstdio>
#include "Board.h"

Board::Board(unsigned int _rows, unsigned int _cols, ::Board::block **_board)
        : rows(_rows), cols(_cols) {
    board = new block *[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new block[cols];
        for (int j = 0; j < cols; ++j) {
            if (_board != NULL)
                board[i][j] = _board[i][j];
            else
                board[i][j] = FREE;
        }
    }
//basic board with borders
    if(_board == NULL) {
        for(int i = 0; i < rows; i++){
            board[i][0] = board[i][cols-1] = BLOCKED;
        }

        for(int i = 0; i < cols; i++){
            board[0][i] = board[rows-1][i] = BLOCKED;
        }
    }
}

Board::~Board() {
    destroy();
}


void Board::print_board() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

Board::Board(const Board &b) {
    copy(b);

}

Board &Board::operator=(const Board &board) {
    if (this == &board)
        return *this;

    destroy();
    copy(board);
    return *this;
}

void Board::copy(const Board &b) {
    rows = b.rows;
    cols = b.cols;
    board = new block *[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new block[cols];
        for (int j = 0; j < cols; ++j) {
            board[i][j] = b.board[i][j];
        }
    }

}

void Board::destroy() {
    for (int i = 0; i < rows; ++i) {
        delete[] board[i];
    }
    delete[] board;
}
