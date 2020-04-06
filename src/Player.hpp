#ifndef Player_hpp
#define Player_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hpp"

class Player {
public:
    Player();
    ~Player();

    int speed = 300;

    void init();
    void render(SDL_Renderer* render);
    void move(SDL_Event& event);

    static const char* PLAYER_FILE;

private:
    SDL_Rect dest;
    SDL_Texture* playerTexture;
    SDL_Rect srcRect, destRect;
    SDL_Texture* playerTex;

    // TODO add parameterized key bindings
    // TODO add parameterized initial positions

};

#endif // Player_hpp
