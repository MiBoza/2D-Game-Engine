#ifndef Object_hpp
#define Object_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Vector2.hpp"
#include <list>

void Print_Rect(const char* string, const SDL_Rect& rect);

struct Texture_Wrapper{
    SDL_Texture* texture;
    SDL_Rect destination;
    SDL_Rect source;

    Texture_Wrapper();
    ~Texture_Wrapper();
};

enum ObjectFlags{
    EMPTY   = 0x00,
    DELETED = 0x01,
    IMAGE   = 0x02,
    TEXT    = 0x04,
    COPYEX  = 0x08
};

class RigidBody;

class Object{
public:
    RigidBody* rb;
    float text_margin = 0;
    float rotation_angle = 0;
    int flags = EMPTY;

    Object(RigidBody* p_rb = NULL);
    void Set_Pos(const Vector2& p_pos);
    void Set_Pos(Vector2&& p_pos);
    void Set_Size(const Vector2& p_size);
    void Flip_Horizontally();
    void Flip_Vertically();
    Vector2 Get_Pos();
    Vector2 Get_Size();
    void Destroy();
    friend class Aggregate;
    friend class Atlas;
    friend class TextureManager;
private:
    Texture_Wrapper image;
    Texture_Wrapper text;
    SDL_Color colour;
    bool outdated = 1;
    Vector2 pos;
    Vector2 size;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    void Update_Dest();
};

#endif // Object_hpp
