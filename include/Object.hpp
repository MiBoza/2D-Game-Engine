#ifndef Object_hpp
#define Object_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector2.hpp"

class Object{
public:
    Object(SDL_Renderer* p_renderer, const Vector2& p_window_res);
    void Set_Texture(const char* path, const Vector2& p_texture_res);
    void Set_Pos(const Vector2& p_pos);
    void Set_Size(const Vector2& p_size);
    void Update_Dest();
    ~Object();
    friend class Game;
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    bool outdated;
    Vector2 window_res;
    Vector2 texture_res;
    Vector2 size;
    Vector2 pos;
    SDL_Rect source;
    SDL_Rect destination;
};

#endif // Object_hpp
