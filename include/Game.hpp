#ifndef Game_hpp
#define Game_hpp

#include "Object.hpp"
// #include <stdio.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

void PrintRect(const SDL_Rect& rect);

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
    Vector2 window_res;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif //Game_hpp
