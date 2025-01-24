#include "Object.hpp"

RigidBody::RigidBody(Vector2& pos_p, bool& p_outdated, const float& p_delta_time):
    pos(pos_p), outdated(p_outdated), delta_time(p_delta_time){}

void RigidBody::Accelerate(Vector2 acceleration){
    //This on top of RigidUpdate should give the correct
    //position and velocity
    acceleration *= delta_time*delta_time;
    pos += acceleration/2;
    velocity += acceleration;
}

Object::Object(const TextureManager* p_texture_manager):
    texture_manager(p_texture_manager){}

void Object::Set_Pos(const Vector2& p_pos){
    pos = p_pos;
    outdated = 1;
}

void Object::Set_Velocity(const Vector2& p_velocity){
    if(rigid_body)
        rigid_body->velocity = p_velocity;
    else
        puts("Error on Set_Velocity. No rigid_body.");
}

void Object::Set_Texture(const int index){
    texture_index = index;
    Vector2 texture_res = texture_manager->resolutions[texture_index];
    source = {0, 0, texture_res.x, texture_res.y};
}

void Object::Accelerate(const Vector2& acceleration){
    rigid_body->Accelerate(acceleration);
}

void Object::Set_Size(const Vector2& p_size){
    size = p_size;
    hidden = 0;
    outdated = 1;
}

Vector2 Object::Get_Pos(){
    if(rigid_body)
        return rigid_body->pos;
    else
        puts("Error on Get_Pos. No rigid_body.");
}

Vector2 Object::Get_Velocity(){
    if(rigid_body)
        return rigid_body->velocity;
    else
        puts("Error on Get_Velocity. No rigid_body.");
}

void Object::Update_Dest(){
    Vector2 corner = pos - size/2;
    destination = {corner.x, corner.y, size.x, size.y};

    outdated = 0;
}

Object::~Object(){
    if(rigid_body)
        delete rigid_body;
}
