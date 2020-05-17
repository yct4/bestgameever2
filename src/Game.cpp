#include "Game.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

const char* START_BUTTON_FILE = "../assets/start_button.png";
const char* CONTINUE_BUTTON_FILE = "../assets/continue.jpg";
const vector<char*> NUMBER_FILES = {"../assets/zero.jpg","../assets/one.png", "../assets/two.jpg", "../assets/three.jpg", "../assets/four.png", "../assets/five.png"};
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

    // initialize start button
    buttonTex = TextureManager::LoadTexture(START_BUTTON_FILE);
    // connects our texture with startButtonRect to control position
    SDL_QueryTexture(buttonTex, NULL, NULL, &startButtonRect.w, &startButtonRect.h);
        // sets initial position of object middle of screen
    startButtonRect.x = (SCREEN_WIDTH - startButtonRect.w) / 2;
    startButtonRect.y = (SCREEN_HEIGHT - startButtonRect.h) / 2;

    // initialize start button
    continueButtonTex = TextureManager::LoadTexture(CONTINUE_BUTTON_FILE);
    // connects our texture with startButtonRect to control position
    SDL_QueryTexture(continueButtonTex, NULL, NULL, &continueButtonRect.w, &continueButtonRect.h);
        // sets initial position of object middle of screen
    continueButtonRect.h /= 4;
    continueButtonRect.w /= 4; 
    continueButtonRect.x = (SCREEN_WIDTH - continueButtonRect.w) / 2;
    continueButtonRect.y = (SCREEN_HEIGHT - continueButtonRect.h) / 2;

    // initialize score number pictures
    for(int i = 0; i < 5; i++) {
        numberTex[i] = TextureManager::LoadTexture(NUMBER_FILES[i]);

        SDL_QueryTexture(numberTex[i], NULL, NULL, &player2ScoreRect.w, &player2ScoreRect.h);
        SDL_QueryTexture(numberTex[i], NULL, NULL, &player1ScoreRect.w, &player1ScoreRect.h);
        player2ScoreRect.w /= 4;
        player2ScoreRect.h /= 4;
        player1ScoreRect.w /= 4;
        player1ScoreRect.h /= 4;

    }
    // sets initial position of player2 score to middle of left half of screen
    player2ScoreRect.x = (SCREEN_WIDTH - player2ScoreRect.w) / 4;
    player2ScoreRect.y = (SCREEN_HEIGHT - player2ScoreRect.h) / 4;
    // sets initial position of player2 score to middle of right half of screen
    player1ScoreRect.x = (SCREEN_WIDTH - player1ScoreRect.w) * 3 / 4;
    player1ScoreRect.y = (SCREEN_HEIGHT - player1ScoreRect.h) / 4;

    // init map
    map = new Map();

    // init game objects
    ball = new Ball();
    ball->init();

    player1 = new Player(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
    int x1_init = (SCREEN_WIDTH - 27 / 1.5) ; // right side -- player image width is 27 and scaling factor is 1.5
    int y1_init = (SCREEN_HEIGHT - 208 / 1.5) / 2; // starts in the middle -- player image height is 27 and scaling factor is 1.5
    player1->init(x1_init, y1_init, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);

    player2 = new Player(SDL_SCANCODE_W, SDL_SCANCODE_S);
    int x2_init = 0; // left side
    int y2_init = (SCREEN_HEIGHT - 208/1.5) / 2; // starts in the middle -- player image height is 27 and scaling factor is 1.5
    player2->init(x2_init, y1_init, SDL_SCANCODE_W, SDL_SCANCODE_S);
}

// TODO: for other games, unsused in pong
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

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN){ 
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { // exit game
                isExited = true;
                break;
            }
            player1->move(event); // player
            player2->move(event);

        } else if (event.type == SDL_QUIT) { // exit game if window is closed
            isExited = true;
            break;
        }
    }
}


void Game::update() {
    isBetweenRounds = ball->move(player1, player2);

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

void Game::renderStartScreen() {
    SDL_Event event; 
    int mouse_x = 0;
    int mouse_y = 0;

    SDL_SetRenderDrawColor(renderer, 0,0,0,0); // set color to write
    SDL_RenderClear(renderer); // clear renderer with latest set color

    // Events mangement
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) { // clicked on start button
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouse_x = event.button.x;
                mouse_y = event.button.y;
                if( ( mouse_x > startButtonRect.x ) && ( mouse_x < startButtonRect.x + startButtonRect.w ) && ( mouse_y > startButtonRect.y ) && ( mouse_y < startButtonRect.y + startButtonRect.h ) ) {
                    isRunning = true;
                    isBetweenRounds = false;
                }
            }
        } else if (event.type == SDL_KEYDOWN){ 
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                isExited = true;
                isRunning = true;
                isBetweenRounds = false;
            }
        } else if (event.type == SDL_QUIT) { // exit game if window is closed
            isExited = true;
            isRunning = true;
            isBetweenRounds = false;
            break;
        }
    } 

    // render start button to screen
    SDL_RenderCopy(renderer, buttonTex, NULL, &startButtonRect);

    // render screen
    SDL_RenderPresent(renderer);

}

void Game::renderRoundScreen() {
    SDL_Event event; 
    int mouse_x = 0;
    int mouse_y = 0;

    SDL_SetRenderDrawColor(renderer, 0,0,0,0); // set color to write
    SDL_RenderClear(renderer); // clear renderer with latest set color

    // Events mangement
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) { // clicked on start button
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouse_x = event.button.x;
                mouse_y = event.button.y;
                if( ( mouse_x > continueButtonRect.x ) && ( mouse_x < continueButtonRect.x + continueButtonRect.w ) && ( mouse_y > continueButtonRect.y ) && ( mouse_y < continueButtonRect.y + continueButtonRect.h ) ) {
                    isRunning = true;
                    isBetweenRounds = false;
                }
            }
        } else if (event.type == SDL_KEYDOWN){ 
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                isExited = true;
                isRunning = true;
                isBetweenRounds = false;
            }
        } else if (event.type == SDL_QUIT) { // exit game if window is closed
            isExited = true;
            isRunning = true;
            isBetweenRounds = false;
            break;
        }
    } 

    SDL_RenderCopy(renderer, continueButtonTex, NULL, &continueButtonRect);

    // render player2 score to screen
    SDL_RenderCopy(renderer, numberTex[player2->getScore()], NULL, &player2ScoreRect);
    SDL_RenderCopy(renderer, numberTex[player1->getScore()], NULL, &player1ScoreRect);

    // reset game if one player reaches score = 5
    int game_over1 = player1->hasWon();
    int game_over2 = player2->hasWon();

    if (game_over1 || game_over2) {
        isRunning = false;
        reset();
    }
    // render screen
    SDL_RenderPresent(renderer);
}

void Game::reset() { // reset player and ball to initial positions and reset ball velocity
    player1->reset();
    player2->reset();
    ball->reset();
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game Cleaned\n");
}