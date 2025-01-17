#ifndef Game_hpp
#define Game_hpp

#include "Object.hpp"
// #include <stdio.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

class Game{
public:
    Game(const char* title, int width, int height, bool fullscreen);
    void Event_Handler();
    void Render();
    void SetUp();
    // void Update();
    ~Game();
    bool running;
    Object* circle = NULL;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif //Game_hpp
