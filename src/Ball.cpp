#include "Ball.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"
#include <math.h>

const char* Ball::BALL_FILE = "../assets/ball.png";
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 800;
const int ANGLE_RANGE = 5;
const int INIT_X_VELOCITY = -4;
const int VELOCITY_INCREMENT = 2;

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
    velocity_x = INIT_X_VELOCITY;
    velocity_y = 0;
}

// returns 1 while between rounds else returns 0
bool Ball::move(Player* player1, Player* player2) {

    // right boundary 
    if (dest.x + dest.w > SCREEN_WIDTH) { // TODO point system, reset ball back to start position and velocity
        player2->incScore();
        return true;
    } else if (dest.x < 0) { // left boundary
        player1->incScore();
        return true;
    }

    //hits player paddle
    else if (SDL_HasIntersection(player1->getRect(), &dest) || SDL_HasIntersection(player2->getRect(), &dest)) {
        velocity_x *= -1;
        velocity_y = rand() % ANGLE_RANGE - (ANGLE_RANGE-1) / 2;
    }

    // rebound bottom/top boundary 

    //lower boundary, dest.x is for upper left corner
    if (dest.y + dest.h >= SCREEN_HEIGHT) {
        dest.y = SCREEN_HEIGHT - dest.h; 
        velocity_y *= -1;
        velocity_y -= VELOCITY_INCREMENT;
        velocity_x += (velocity_x > 0) ? VELOCITY_INCREMENT : -VELOCITY_INCREMENT;
    }

    // upper boundary, dest.y is for upper left corner of the ball
    if (dest.y <= 0) {
        dest.y = 0; 
        velocity_y *= -1;
        velocity_y += VELOCITY_INCREMENT;
        velocity_x += (velocity_x > 0) ? VELOCITY_INCREMENT : -VELOCITY_INCREMENT;
    }

    dest.x += velocity_x;
    dest.y += velocity_y;

    return false;
}

void Ball::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, ballTex, NULL, &dest);
}

void Ball::reset() {
    // sets initial x-position of object middle of screen
    dest.x = (SCREEN_WIDTH - dest.w) / 2;

    // sets initial y-position of object middle of screen
    dest.y = (SCREEN_HEIGHT - dest.h) / 2;

    // speed of ball
    velocity_x = INIT_X_VELOCITY;
    velocity_y = 0;
}

void Ball::resetPosition() {
        // sets initial x-position of object middle of screen
    dest.x = (SCREEN_WIDTH - dest.w) / 2;

    // sets initial y-position of object middle of screen
    dest.y = (SCREEN_HEIGHT - dest.h) / 2;
}