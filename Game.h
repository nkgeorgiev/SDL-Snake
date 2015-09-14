//
// Created by nikolay on 14.09.15.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Snake.h"
#include <SDL2/SDL.h>

class Game {
    const int BLOCK_SIZE = 20;
    const int SPEED = 300;
    unsigned screen_width, screen_height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Snake snake;

    bool init();

    void close();

public:
    Game(unsigned, unsigned);

    ~Game();

    void handleEvent(SDL_Event &e);

    void render();

    void run();


};


#endif //SNAKE_GAME_H
