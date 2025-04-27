#ifndef Object_hpp
#define Object_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector2.hpp"
#include <list>

void Print_Rect(const char* string, const SDL_Rect& rect);

enum ObjectFlags{
    EMPTY   = 0x00,
    DELETED = 0x01,
    RENDER  = 0x02,
    COPYEX  = 0x04,
};

class RigidBody;

class Object{
public:
    RigidBody* rb;

    Object(RigidBody* p_rb = NULL);
    void Set_Pos(const Vector2& p_pos);
    void Set_Pos(Vector2&& p_pos);
    void Set_Size(const Vector2& p_size);
    void Rotate(float angle);
    void Flip_Horizontally();
    void Flip_Vertically();
    Vector2 Get_Pos();
    Vector2 Get_Size();
    void Destroy();
    friend class Aggregate;
    friend class Atlas;
private:
    SDL_Texture* texture;
    bool outdated = 1;
    Vector2 pos;
    float rotation_angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    int flags = EMPTY;
    Vector2 size;
    SDL_Rect source;
    SDL_Rect destination;

    void Update_Dest();
};

#endif // Object_hpp
