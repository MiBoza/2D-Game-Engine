#include "Object.hpp"

void Print_Rect(const char* string, const SDL_Rect& rect){
    printf("%s[%i, %i, %i, %i]\n", string, rect.x, rect.y, rect.h, rect.w);
}

Object::Object(RigidBody* p_rb):
    rb(p_rb), size({60, 60}){}

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
