#ifndef RigidBody_hpp
#define RigidBody_hpp

#include "Object.hpp"
#include <cmath>

struct Line{
    //hy = kx + l
    float h, k, l;
};

class RigidBody : public Object{
public:
    const Uint32& delta_time;
    Vector2 velocity = {0, 0};
    Vector2 acceleration = {0, 0};

    RigidBody(const Uint32& delta_time, const TextureManager* p_texture_manager);
    void Rigid_Update();
    void Collide(const Line& line); //Calculates collision with a line
};

#endif //RigidBody_hpp
