#ifndef Object_hpp
#define Object_hpp

#include "Window_Data.hpp"
#include <list>
using std::list;

class RigidBody;

class Object{
public:
    RigidBody* rb;
    float text_margin = 0;
    float rotation_angle = 0;
    int flags = EMPTY;

    Object(RigidBody* p_rb = NULL);
    void Set_Pos(const Vector2& p_pos);
    void Set_Size(const Vector2& p_size);
    void Set_Behaviour(Behaviour* behaviour);
    void Flip_Horizontally();
    void Flip_Vertically();
    Vector2 Get_Pos();
    Vector2 Get_Size();
    void Update_Dest();
    void Destroy();
private:
    Texture_Wrapper image;
    Texture_Wrapper text;
    SDL_Color colour;
    Vector2 pos;
    Vector2 size;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Behaviour* behaviour = NULL;

    ~Object();

    friend class Atlas;
    friend class Silly_Core;
    friend class RigidBody;
    friend class TextureManager;
};

#endif // Object_hpp
