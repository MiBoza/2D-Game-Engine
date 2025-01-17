#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Object{
public:
    Object(SDL_Renderer* p_renderer);
    void Set_Texture(const char* path);
    ~Object();
    friend class Game;
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect destination;
};

#endif // Object_hpp
