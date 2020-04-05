#include "TextureManager.hpp"
#include "Game.hpp"

// TODO create ball class - move across screen

GameObject::GameObject(const char* texturesheet) {

    objTexture = TextureManager::LoadTexture(texturesheet);
}

void GameObject::Update() {
    xpos = 0;
    ypos = 0;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}