#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Map.hpp"
#include "Ball.hpp"
#include "Player.hpp"

class Game {

    public:
        int close = 0;

        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void DrawMap();
        void renderBlock(SDL_Window* window, SDL_Rect* box);
        void handleEvents();
        void update();
        void render();
        void clean();
        void reset();

        void initStartScreen();
        void renderStartScreen();

        void playerJump();
        void playerRun();

        static SDL_Renderer* renderer;

        bool running() {
            return isRunning;
        };

        bool exiting() {
            return isExited;
        };



    private:
        SDL_Window* window;
        bool isRunning;
        bool isExited;
        int count = 0;
        Map* map;
        Ball* ball;
        Player* player1;
        Player* player2;

        // start button
        SDL_Rect startButtonRect;
        SDL_Texture* buttonTex;
};

#endif // Game_hpp
