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

        void renderStartScreen();
        void renderRoundScreen();

        static SDL_Renderer* renderer;

        bool running() {
            return isRunning;
        };

        bool exiting() {
            return isExited;
        };

        bool waitingBetweenRounds() {
            return isBetweenRounds;
        };



    private:
        SDL_Window* window;
        bool isRunning;
        bool isExited;
        bool isBetweenRounds;
        Map* map;
        Ball* ball;
        Player* player1;
        Player* player2;

        // start button
        SDL_Rect startButtonRect;
        SDL_Texture* buttonTex;

        //continue button
        SDL_Rect continueButtonRect;
        SDL_Texture* continueButtonTex;

        //banners
        SDL_Rect player1BannerRect;
        SDL_Texture* player1BannerTex;
        SDL_Rect player2BannerRect;
        SDL_Texture* player2BannerTex;
        SDL_Rect gameOverRect;
        SDL_Texture* gameOverTex;

        // score
        SDL_Rect player1ScoreRect;
        SDL_Rect player2ScoreRect;
        SDL_Texture* numberTex[]; // must be last line of class
};

#endif // Game_hpp
