//
// Created by nikolay on 14.09.15.
//

#include "Snake.h"


Snake::Snake(unsigned rows, unsigned cols, unsigned pts)
        : board(rows, cols), direction(LEFT), dead(false),
          result(0), pts_per_apple(pts), snake() { }

bool Snake::move(Direction d) {

    bool grow = false;
    int x = snake.front().first;
    int y = snake.front().second;
    unsigned rows = board.get_rows();
    unsigned cols = board.get_cols();
    switch (d) {
        case UP:
            if (direction == DOWN) return true;
            if (!move((x - 1 + rows) % rows, y, grow)) return false;
            break;
        case DOWN:
            if (direction == UP) return true;
            if (!move((x + 1) % rows, y, grow)) return false;
            break;
        case LEFT:
            if (direction == RIGHT) return true;
            if (!move(x, (y - 1 + cols) % cols, grow)) return false;
            break;
        case RIGHT:
            if (direction == LEFT) return true;
            if (!move(x, (y + 1) % cols, grow)) return false;
            break;
    }
    direction = d;
    if (!grow) {
        pos p = snake.back();
        board.set_block(p.first, p.second, Board::FREE);
        snake.pop_back();

    }
    else {
        result += pts_per_apple;
        generate_apple();
    }
}

bool Snake::move(unsigned int x, unsigned int y, bool &grow) {
    if (board.is_apple(x, y)) {
        grow = true;
    } else if (!board.is_free(x, y)) {
        dead = true;
        return false;

    }
    snake.push_front(std::make_pair(x, y));
    board.set_block(x, y, Board::SNAKE);
    if (board.is_apple(x, y)) {
        grow = true;

    }
    return true;
}

bool Snake::move() {
    return move(direction);
}


void Snake::init_snake() {
    srand(time(NULL));
    int x, y;
    do {
        x = rand() % board.get_rows();
        y = rand() % board.get_cols();
    } while (!board.is_free(x, y));

    snake.push_back(std::make_pair(x, y));
    board.set_block(x, y, Board::SNAKE);

    generate_apple();
}

void Snake::generate_apple() {
    srand(time(NULL));
    int x, y;
    do {
        x = rand() % board.get_rows();
        y = rand() % board.get_cols();
    } while (!board.is_free(x, y));
    board.set_block(x, y, Board::APPLE);
}
