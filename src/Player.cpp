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

    // sets initial x-position of object
    dest.x = _x;
    init_x = _x;

    // sets initial y-position of object
    dest.y = _y;
    init_y = _y;

    // speed of player
    speed = 300;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, playerTex, NULL, &dest); // player
}

SDL_Rect* Player::get_Rect() {
    return &dest;
}

void Player::move(SDL_Event& event) {
    // keyboard API for key pressed
    if (event.key.keysym.scancode == scancode_up) {
        dest.y -= speed / 10;
    } else if (event.key.keysym.scancode == scancode_down) {
        dest.y += speed / 10;
    }

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

void Player::reset() {
    // sets initial x-position of object
    dest.x = init_x;

    // sets initial y-position of object
    dest.y = init_y;
}
