#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game{
public:
    Game(const char* title, int width, int height, bool fullscreen);
    void Event_Handler();
    void Render();
    // void Update();
    ~Game();
    bool running;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif //Game_hpp
