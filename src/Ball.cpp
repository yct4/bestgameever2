#include "Ball.hpp"
#include "TextureManager.hpp"
#include <math.h>

const char* Ball::BALL_FILE = "../assets/ball.png";
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 800;
const int ANGLE_RANGE = 4;

Ball::Ball() {}
Ball::~Ball() {}

void Ball::init() {
    // loads file as texture
    ballTex = TextureManager::LoadTexture(BALL_FILE);
    

    // connects our texture with dest to control position
    SDL_QueryTexture(ballTex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 10;
    dest.h /= 10;

    // sets initial x-position of object middle of screen
    dest.x = (SCREEN_WIDTH - dest.w) / 2;

    // sets initial y-position of object middle of screen
    dest.y = (SCREEN_HEIGHT - dest.h) / 2;

    // speed of ball
    velocity_x = -2;
    velocity_y = 0;
}

void Ball::move(const SDL_Rect* player_rect) {

    // right boundary 
    if (dest.x + dest.w > SCREEN_WIDTH) {
        dest.x = SCREEN_WIDTH - dest.w; // TODO game over
    } else if (dest.x < 0) { // left boundary
        dest.x = 0; 
    }

    //hits player paddle
    else if (SDL_HasIntersection(player_rect, &dest)) {
        velocity_x *= -1;
        velocity_y = rand() % ANGLE_RANGE - (ANGLE_RANGE-1);
        // velocity_y =  dest.y - player_rect->y;
    }

    // rebound bottom/top boundary 

    //lower boundary
    if (dest.y + dest.h >= SCREEN_HEIGHT) {
        dest.y = SCREEN_HEIGHT - dest.h; 
        velocity_y *= -1;
    }

    // upper boundary 
    if (dest.y - dest.h <= 0) {
        dest.y = 0; 
        velocity_y *= -2;
    }

    dest.x += velocity_x;
    dest.y += velocity_y;

}

void Ball::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, ballTex, NULL, &dest);
}

void Ball::change_spd() {}