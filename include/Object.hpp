#ifndef Object_hpp
#define Object_hpp

#include "TextureManager.hpp"
#include <list>

class Object{
public:
    int texture_index;

    Object(const TextureManager* p_texture_manager);
    void Set_Pos(const Vector2& p_pos);
    void Set_Size(const Vector2& p_size);
    void Set_Texture(const int index);
    Vector2 Get_Pos();
    void Update_Dest();
    // ~Object();
    friend class Game;
protected:
    const TextureManager* texture_manager;
    bool outdated = 1;
    Vector2 pos;
private:
    Vector2 size;
    SDL_Rect source;
    SDL_Rect destination;
    bool hidden = 1;
};

// struct RigidBody : public Object{
struct RigidBody : public Object{
    const Uint32& delta_time;
    Vector2 velocity = {0, 0};
    Vector2 acceleration = {0, 0};

    RigidBody(const Uint32& delta_time, const TextureManager* p_texture_manager);
    void Update();
};

#endif // Object_hpp
