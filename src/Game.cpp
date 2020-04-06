#include "Game.hpp"
#include "TextureManager.hpp"
#include <stdio.h>

const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 800;
SDL_Renderer* Game::renderer = nullptr;

Game::Game() {}
Game::~Game() {}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    // init screen
    int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL ERROR: %d", SDL_GetError());
        isRunning = false;
        return;
    }
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
        printf("window created!\n");
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        printf("renderer created!\n");
    }

    // init other variables
    isRunning = true;

    // init map
    map = new Map();

    // init game objects
    ball = new Ball();
    ball->init();

    player1 = new Player();
    player1->init();

}


void Game::DrawMap() {
    int type = 0;

    for(int row = 0; row < 20; row++) {
        for(int col = 0;  col < 25; col++) {
            type = map->map[row][col];

            map->dest.x = col * 32;
            map->dest.y = row * 32;

            switch (type) {
                case 0:
                    TextureManager::Draw(map->water, map->src, map->dest);
                    break;
                case 1: 
                    TextureManager::Draw(map->grass, map->src, map->dest);
                    break;
                case 2:
                    TextureManager::Draw(map->dirt, map->src, map->dest);
                    break;
                default:
                    break;
            }
        }
    }
}


void Game::handleEvents() {
    SDL_Event event; 

    // Events mangement 
    while (SDL_PollEvent(&event)) { 

        if (event.type == SDL_KEYDOWN){ 
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { // exit game
                isRunning = false;
                break;
            }
            player1->move(event); // player

        } else if (event.type == SDL_QUIT) { // exit game if window is closed
            isRunning = false;
            break;
        }
    } 

}


void Game::update() {
    count++;
    destRect.h = 128;
    destRect.w = 128;
    ball->move();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255,255,255,255); // set color to write
    SDL_RenderClear(renderer); // clear renderer with latest set color

    map->DrawMap();

    //render game objects
    player1->render(renderer); // player
    ball->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game Cleaned\n");
}