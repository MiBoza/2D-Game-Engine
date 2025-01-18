#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Vector2{
    int x, y;

    Vector2 operator-(const Vector2& v);
    Vector2 operator*(float A);
    Vector2 operator/(float A);
    void operator+=(const Vector2& v);
};

void Print_Vector2(const Vector2& v);

class Object{
public:
    Object(SDL_Renderer* p_renderer, const Vector2& p_window_res);
    void Set_Texture(const char* path, const Vector2& p_texture_res);
    void Set_Pos(const Vector2& p_pos);
    void Set_Scale(float p_scale);
    void Update_Dest();
    ~Object();
    friend class Game;
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    float scale;
    bool outdated;
    Vector2 window_res;
    Vector2 texture_res;
    Vector2 pos;
    SDL_Rect source;
    SDL_Rect destination;
};

#endif // Object_hpp
