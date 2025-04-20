#include "Object.hpp"

Object::Object(const TextureManager* p_texture_manager, RigidBody* p_rb):
    texture_manager(p_texture_manager), rb(p_rb), size({60, 60}){}

void Object::Set_Pos(const Vector2& p_pos){
    pos = p_pos;
    outdated = 1;
}

void Object::Set_Pos(Vector2&& p_pos){
    pos = p_pos;
    outdated = 1;
}

void Object::Set_Size(const Vector2& p_size){
    size = p_size;
    outdated = 1;
}

void Object::Set_Texture(const int index){
    flags |= RENDER;
    texture_index = index;
    Vector2 texture_res = texture_manager->resolutions[texture_index];
    source = {0, 0, texture_res.x, texture_res.y};
}

Vector2 Object::Get_Pos(){
    return pos;
}

Vector2 Object::Get_Size(){
    return size;
}

void Object::Update_Dest(){
    Vector2 corner = pos - size/2;
    destination = {corner.x, corner.y, size.x, size.y};

    outdated = 0;
}

void Object::Destroy(){
    flags |= DELETED;
}
