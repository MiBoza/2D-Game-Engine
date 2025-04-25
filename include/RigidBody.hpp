#ifndef RigidBody_hpp
#define RigidBody_hpp

#include "Object.hpp"

struct Line{
    //hy = kx + l
    float h, k, l;
};

class RigidBody{
public:
    const Uint32& delta_time;
    Object* object;
    Vector2 velocity = {0, 0};
    Vector2 acceleration = {0, 0};

    RigidBody(const Uint32& p_delta_time, Object* p_object);
    void Rigid_Update();
    void Collide(const Line& line); //Calculates collision with a line
    void Set_Pos(const Vector2& p_pos);
    void Set_Size(const Vector2& p_size);

    Vector2 Get_Pos();
    Vector2 Get_Size();
};

#endif //RigidBody_hpp
