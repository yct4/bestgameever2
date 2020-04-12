#include "Player.hpp"

#include "TextureManager.hpp"

const char* Player::PLAYER_FILE = "../assets/pong_player.png";
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 800;

Player::Player(int _up, int _down) : scancode_up(_up), scancode_down(_down) {};
Player::~Player() {}

void Player::init(int _x, int _y, int _up, int _down) {
        // loads file as texture
    playerTex = TextureManager::LoadTexture(PLAYER_FILE);
    

    // connects our texture with dest to control position
    SDL_QueryTexture(playerTex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 1.5;
    dest.h /= 1.5;

    // sets initial x-position of object middle of screen
    dest.x = _x;//(SCREEN_WIDTH - dest.w) / 2;

    // sets initial y-position of object middle of screen
    dest.y = _y;//(SCREEN_HEIGHT - dest.h) / 2;

    // keybindings
    // scancode_up = _up;
    // scancode_down = _down;

    // speed of player
    speed = 300;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, playerTex, NULL, &dest); // player
}

void Player::move(SDL_Event& event) {
    // keyboard API for key pressed
    if (event.key.keysym.scancode == scancode_up) {
        dest.y -= speed / 10;
    } else if (event.key.keysym.scancode == scancode_down) {
        dest.y += speed / 10;
    }
    // 'this' can't be part of const expression
    // switch (event.key.keysym.scancode) { 
    //     case test: 
    //         dest.y -= speed / 30; 
    //         break;
    //     // case scancode_up: 
    //     //     dest.y -= speed / 30; 
    //     //     break; 
    //     // case scancode_down: 
    //     //     dest.y += speed / 30; 
    //     //     break; 
    //     default:
    //         break;
    // }
    // switch (event.key.keysym.scancode) { 
    //     case SDL_SCANCODE_W: 
    //     case SDL_SCANCODE_UP: 
    //         dest.y -= speed / 30; 
    //         break; 
    //     case SDL_SCANCODE_A: 
    //     case SDL_SCANCODE_LEFT: 
    //         dest.x -= speed / 30; 
    //         break; 
    //     case SDL_SCANCODE_S: 
    //     case SDL_SCANCODE_DOWN: 
    //         dest.y += speed / 30; 
    //         break; 
    //     case SDL_SCANCODE_D: 
    //     case SDL_SCANCODE_RIGHT: 
    //         dest.x += speed / 30; 
    //         break; 
    //     default:
    //         break;
    // }

    // dest.y += speed / 30;
    // dest.x += speed / 30;

    // right boundary 
    if (dest.x + dest.w > SCREEN_WIDTH) {
        dest.x = SCREEN_WIDTH - dest.w; 
    }

    // left boundary 
    if (dest.x < 0) {
        dest.x = 0; 
    }

    // bottom boundary 
    if (dest.y + dest.h > SCREEN_HEIGHT) {
        dest.y = SCREEN_HEIGHT - dest.h; 
    }

    // upper boundary 
    if (dest.y < 0) {
        dest.y = 0; 
    }

}