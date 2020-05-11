#include <stdio.h>
#include <SDL2/SDL.h>
#include "Game.hpp"

Game* game;

void waitInStartScreen();
void waitInRoundScreen();

int main(int argc, char *argv[]) {

    const int FPS = 40;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("test game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    waitInStartScreen();

    while (!game->exiting()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart; // how long handleever, update, and render takes
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        if(game->waitingBetweenRounds()) {
            waitInRoundScreen();
        }

        if(!game->running()) {
            waitInStartScreen();
        }
    }


    game->clean();

    return EXIT_SUCCESS;
}

void waitInStartScreen() {
    while (!game->running()) {
        game->renderStartScreen();
    }
}

void waitInRoundScreen() {
    while (game->waitingBetweenRounds()) {
        game->renderRoundScreen();
    }
}
