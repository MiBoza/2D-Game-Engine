#include "Object.hpp"

void Print_Vector2(const Vector2& v){
    printf("[%i, %i]\n", v.x, v.y);
}

Vector2 Vector2::operator-(const Vector2& v){
    Vector2 result = {x - v.x, y - v.y};
    return result;
}
Vector2 Vector2::operator*(float A){
    Vector2 result = {static_cast<float>(x)*A, static_cast<float>(y)*A};
    return result;
}
Vector2 Vector2::operator/(float A){
    Vector2 result = {static_cast<float>(x)/A, static_cast<float>(y)/A};
    return result;
}

void Vector2::operator+=(const Vector2& v){
    x += v.x;
    y += v.y;
}

Object::Object(SDL_Renderer* p_renderer, const Vector2& p_window_res):
    texture(NULL), window_res(p_window_res), pos(window_res/2),
    scale(1){
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

void Object::Set_Scale(float p_scale){
    scale = p_scale;
    outdated = 1;
}

void Object::Update_Dest(){
    Vector2 dest_res = texture_res*scale;
    Vector2 corner = pos - dest_res/2;
    destination = {corner.x, corner.y, dest_res.x, dest_res.y};

    outdated = 0;
}

Object::~Object(){
    if(texture)
        SDL_DestroyTexture(texture);
}
