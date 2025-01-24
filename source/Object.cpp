#include "Object.hpp"

Object::Object(const TextureManager* p_texture_manager):
    texture_manager(p_texture_manager), size({60, 60}){}

void Object::Set_Pos(const Vector2& p_pos){
    pos = p_pos;
    outdated = 1;
}

void Object::Set_Size(const Vector2& p_size){
    size = p_size;
    outdated = 1;
}

void Object::Set_Texture(const int index){
    hidden = 0;
    texture_index = index;
    Vector2 texture_res = texture_manager->resolutions[texture_index];
    source = {0, 0, texture_res.x, texture_res.y};
}

Vector2 Object::Get_Pos(){
    return pos;
}

void Object::Update_Dest(){
    Vector2 corner = pos - size/2;
    destination = {corner.x, corner.y, size.x, size.y};

    outdated = 0;
}

// Object::~Object(){
// }

RigidBody::RigidBody(const Uint32& p_delta_time, const TextureManager* p_texture_manager):
    delta_time(p_delta_time),
    Object(p_texture_manager){}

void RigidBody::Update(){
    outdated = 1;
    pos += velocity*delta_time;
    if(acceleration.Not_Zero()){
        pos += acceleration*delta_time*delta_time/2;
        velocity += acceleration;
    }
}
