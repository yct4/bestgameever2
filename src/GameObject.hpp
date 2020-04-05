#ifndef GameObject_hpp
#define GameObject_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class GameObject {
public:
    GameObject(const char* texturesheet);
    ~GameObject();

    void Update();
    void Render();

private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

#endif // GameObject_hpp