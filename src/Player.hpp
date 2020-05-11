#ifndef Player_hpp
#define Player_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hpp"

class Player {
public:  
    Player(int _up, int _down);
    ~Player();

    int speed = 300;

    void init(int _x, int _y, int _up, int _down);
    void render(SDL_Renderer* render);
    void move(SDL_Event& event);
    void reset();
    bool hasWon();
    int getScore();
    void incScore();
    SDL_Rect* getRect();

    static const char* PLAYER_FILE;

private:
    SDL_Rect dest;
    SDL_Texture* playerTexture;
    SDL_Rect srcRect, destRect;
    SDL_Texture* playerTex;
    const int scancode_up;
    const int scancode_down;

    int init_x;
    int init_y;

    int score;

};

#endif // Player_hpp
