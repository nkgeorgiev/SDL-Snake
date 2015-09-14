//
// Created by nikolay on 14.09.15.
//

#include "Game.h"

bool Game::init() {
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        window = SDL_CreateWindow("SDL Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //Create vsynced renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}

void Game::close() {

    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

Game::Game(unsigned w, unsigned h) : screen_width(w), screen_height(h),
                                     snake(screen_height / BLOCK_SIZE, screen_width / BLOCK_SIZE) {
    snake.init_snake();
}

Game::~Game() {

}

void Game::handleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                snake.move(Snake::UP);
                break;
            case SDLK_DOWN:
                snake.move(Snake::DOWN);
                break;
            case SDLK_LEFT:
                snake.move(Snake::LEFT);
                break;
            case SDLK_RIGHT:
                snake.move(Snake::RIGHT);
                break;
            default:
                break;
        }
    }


}

void Game::run() {
    Uint32 start_time = SDL_GetTicks(), curr_time;
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        printf("dimensions %d %d\n", screen_height, screen_width);
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //While application is running
        while (!quit) {
            //quit if dead
            if (snake.is_dead()) {
                quit = true;
                char text[50];
                sprintf(text, "Sorry! You have lost! Your score is %d!\n", snake.get_result());
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Game Over", text, NULL);
            }

            //move after SPEED ms
            curr_time = SDL_GetTicks();
            if (curr_time - start_time > SPEED) {
                if (!snake.move())
                    quit = false;
                start_time = curr_time;
            }
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                }

                //Handle input for the dot
                handleEvent(e);
            }

            //Clear screen
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            //Render objects
            render();

            //Update screen
            SDL_RenderPresent(renderer);
        }

    }


    //Free resources and close SDL
    close();


}

void Game::render() {

    Board board = snake.get_board();
    for (int i = 0; i < board.get_rows(); ++i) {
        for (int j = 0; j < board.get_cols(); ++j) {
            if (board.is_apple(i, j)) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
            } else if (board.is_free(i, j)) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
            } else if (board.is_blocked(i, j))
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
            else
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);

            SDL_Rect rect{j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

}
