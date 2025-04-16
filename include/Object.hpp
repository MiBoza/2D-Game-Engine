#ifndef Object_hpp
#define Object_hpp

#include "TextureManager.hpp"
#include <list>

enum ObjectFlags{
    EMPTY   = 0x0,
    DELETED = 0x1,
    RENDER  = 0x2,
};

class RigidBody;

class Object{
public:
    int texture_index;
    RigidBody* rb;

    Object(const TextureManager* p_texture_manager, RigidBody* p_rb = NULL);
    void Set_Pos(const Vector2& p_pos);
    void Set_Size(const Vector2& p_size);
    void Set_Texture(const int index);
    Vector2 Get_Pos();
    Vector2 Get_Size();
    void Update_Dest();
    void Destroy();
    friend class Game;
protected:
    const TextureManager* texture_manager;
    bool outdated = 1;
    Vector2 pos;
    int flags = EMPTY;
private:
    Vector2 size;
    SDL_Rect source;
    SDL_Rect destination;
};

#endif // Object_hpp
