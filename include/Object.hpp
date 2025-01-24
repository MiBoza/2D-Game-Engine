#ifndef Object_hpp
#define Object_hpp

#include "TextureManager.hpp"
#include <list>

struct RigidBody{
    RigidBody(Vector2& pos_p, bool& p_outdated, const float& p_delta_time);
    void Accelerate(Vector2 acceleration);

    const float& delta_time;
    Vector2& pos;
    bool& outdated;
    Vector2 velocity = {0, 0};
};

class Object{
public:
    int texture_index;

    Object(const TextureManager* p_texture_manager);
    void Set_Pos(const Vector2& p_pos);
    void Set_Velocity(const Vector2& p_velocity);
    void Accelerate(const Vector2& acceleration);
    void Set_Size(const Vector2& p_size);
    void Set_Texture(const int index);
    Vector2 Get_Pos();
    Vector2 Get_Velocity();
    void Update_Dest();
    ~Object();
    friend class Game;
private:
    const TextureManager* texture_manager;
    RigidBody* rigid_body = NULL;
    bool hidden = 1;
    bool outdated;
    Vector2 size;
    Vector2 pos;
    SDL_Rect source;
    SDL_Rect destination;
};

#endif // Object_hpp
