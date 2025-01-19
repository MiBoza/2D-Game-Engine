#include "Object.hpp"

Object::Object(SDL_Renderer* p_renderer, const Vector2& p_window_res):
    texture(NULL), window_res(p_window_res), pos(window_res/2),
    size(window_res/10){
    renderer = p_renderer;
}

void Object::Set_Texture(const char* path, const Vector2& p_texture_res){
    texture = IMG_LoadTexture(renderer, path);
    texture_res = p_texture_res;
    source = {0, 0, texture_res.x, texture_res.y};
}

void Object::Set_Pos(const Vector2& p_pos){
    pos = p_pos;
    outdated = 1;
}

void Object::Set_Size(const Vector2& p_size){
    size = p_size;
    outdated = 1;
}

void Object::Update_Dest(){
    Vector2 corner = pos - size/2;
    // printf("[%f, %f, %f, %f]\n", corner.x, corner.y, size.x, size.y);
    destination = {corner.x, corner.y, size.x, size.y};

    outdated = 0;
}

Object::~Object(){
    if(texture)
        SDL_DestroyTexture(texture);
}
