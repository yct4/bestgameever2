#ifndef Ball_hpp
#define Ball_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hpp"
#include "Player.hpp"

class Ball {
public: 
    Ball();
    ~Ball();



    void init();
    bool move(Player* player1, Player* player2);
    void render(SDL_Renderer* render);
    void reset();
    void resetPosition();

    static const char* BALL_FILE;

private:
    SDL_Rect dest;
    SDL_Rect srcRect, destRect;
    SDL_Texture* ballTex;

    int velocity_x;
    int velocity_y;

};

#endif // Ball_hpp