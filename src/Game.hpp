#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameObject.hpp"
#include "Map.hpp"

class Game {

    public:
        int close = 0;

        // speed of box
        int speed = 300;
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void DrawMap();
        void renderBlock(SDL_Window* window, SDL_Rect* box);
        void handleEvents();
        void update();
        void render();
        void clean();

        void playerJump();
        void playerRun();

        static SDL_Renderer* renderer;

        bool running() {
            return isRunning;
        };



    private:
        SDL_Window* window;
        bool isRunning;
        int count = 0;
        SDL_Rect dest;
        SDL_Texture* playerTexture;
        SDL_Rect srcRect, destRect;
        SDL_Texture* playerTex;
        GameObject* player;
        Map* map;
};

#endif // Game_hpp
