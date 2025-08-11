#include "Object.hpp"

void Print_Rect(const char* string, const SDL_Rect& rect){
    printf("%s[%i, %i, %i, %i]\n", string, rect.x, rect.y, rect.h, rect.w);
}

Texture_Wrapper::Texture_Wrapper():
    texture(NULL){}

Texture_Wrapper::~Texture_Wrapper(){
    SDL_DestroyTexture(texture);
}

Object::Object(RigidBody* p_rb):
    rb(p_rb), size({60, 60}){
    text.texture = NULL;
}

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

void Object::Flip_Horizontally(){
    //Brute force, but XOR should be supported on flags
    int flip_i = static_cast<int>(flip);
    flip_i ^= SDL_FLIP_HORIZONTAL;
    flip = static_cast<SDL_RendererFlip>(flip_i);
}

void Object::Flip_Vertically(){
    int flip_i = static_cast<int>(flip);
    flip_i ^= SDL_FLIP_VERTICAL;
    flip = static_cast<SDL_RendererFlip>(flip_i);
}

Vector2 Object::Get_Pos(){
    return pos;
}

Vector2 Object::Get_Size(){
    return size;
}

void Object::Update_Dest(){
    if(flags & IMAGE){
        Vector2 corner = pos - size/2;
        image.destination = {corner.x, corner.y, size.x, size.y};
    }
    if(flags & TEXT){
        Vector2 tx_size({text.source.w, text.source.h});
        // Print_Vector2("tx_size = ", tx_size);
        Vector2 corner = pos - tx_size/2;
        text.destination = {corner.x, corner.y, tx_size.x, tx_size.y};
    }
    outdated = 0;
}

void Object::Destroy(){
    flags |= DELETED;
}
