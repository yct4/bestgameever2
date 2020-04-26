#include "Game.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
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
    isRunning = false;

    // init map
    map = new Map();

    // init game objects
    ball = new Ball();
    ball->init();

    player1 = new Player(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
    int x1_init = (SCREEN_WIDTH - 20 * player1->get_Rect()->w) ; // right side
    int y1_init = (SCREEN_HEIGHT - player1->get_Rect()->h) / 2; // starts in the middle
    player1->init(x1_init, y1_init, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);

    player2 = new Player(SDL_SCANCODE_W, SDL_SCANCODE_S);
    int x2_init = 0; // left side
    int y2_init = (SCREEN_HEIGHT - player2->get_Rect()->h) / 2; // starts in the middle
    player2->init(x2_init, y1_init, SDL_SCANCODE_W, SDL_SCANCODE_S);
}

// TODO game start screen
/* detect hitting a button to start the game
// TODO game end screen
detect hitting a button to end the game
*/
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
        // TODO check when game is over (the game is over when the ball hits either right or left walls)
            // set isRunning = false
        if (event.type == SDL_KEYDOWN){ 
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { // exit game
                isRunning = false;
                break;
            }
            player1->move(event); // player
            player2->move(event);

        } else if (event.type == SDL_QUIT) { // exit game if window is closed
            isRunning = false;
            break;
        }
    } 

}


void Game::update() {
    count++;
    ball->move(player1->get_Rect());
    ball->move(player2->get_Rect());
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255,255,255,255); // set color to write
    SDL_RenderClear(renderer); // clear renderer with latest set color

    //render game objects
    player1->render(renderer); // player
    player2->render(renderer);
    ball->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game Cleaned\n");
}