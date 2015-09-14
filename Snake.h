//
// Created by nikolay on 14.09.15.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


#include <list>
#include <cstdlib>
#include <ctime>
#include "Board.h"

typedef std::pair<int, int> pos;

class Snake {
public:
    enum Direction {
        LEFT = 0,
        RIGHT = 1,
        UP = 2,
        DOWN = 3,
        NONE = 4
    };

private:
    unsigned pts_per_apple;
    Board board;
    std::list<pos> snake;
    unsigned result;
    Direction direction;

    bool dead;

    bool move(unsigned, unsigned, bool &);

    void generate_apple();

public:

    Snake(unsigned = 15, unsigned = 30, unsigned = 10);

    void init_snake();

    bool move(Direction);

    bool move();

    unsigned get_result() const {
        return result;
    }

    Board get_board() const {
        return board;
    }

    std::list<pos> get_snake() const {
        return snake;
    }

    void set_board(Board &b) {
        board = b;
    }

    bool is_dead() const {
        return dead;
    }


};


#endif //SNAKE_SNAKE_H
