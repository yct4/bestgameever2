#ifndef Ball_hpp
#define Ball_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hpp"

class Ball {
public: 
    Ball();
    ~Ball();

    int speed = 300;

    void init();
    void move(const SDL_Rect* player);
    void render(SDL_Renderer* render);
    void change_spd();

    static const char* BALL_FILE;

private:
    SDL_Rect dest;
    SDL_Texture* ballTexture;
    SDL_Rect srcRect, destRect;
    SDL_Texture* ballTex;


};

#endif // Ball_hpp