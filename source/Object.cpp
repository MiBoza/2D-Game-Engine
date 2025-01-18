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

Object::Object(SDL_Renderer* p_renderer, const Vector2& p_window_res):
    texture(NULL), window_res(p_window_res), pos(window_res/2),
    scale(1){
    renderer = p_renderer;
}

void Object::Set_Texture(const char* path){
    texture = IMG_LoadTexture(renderer, path);
}

void Object::Set_Pos(const Vector2& p_pos){
    pos = p_pos;
    outdated = 1;
}

void Object::Set_Scale(float p_scale){
    scale = p_scale;
    outdated = 1;
}

void Object::Update_Rects(){
    Vector2 texture_res = {787, 787};
    printf("scale = %f\n", scale);
    Vector2 dest_res = texture_res*scale;
    Vector2 corner = pos - dest_res/2;
    source = {0, 0, texture_res.x, texture_res.y};
    destination = {corner.x, corner.y, dest_res.x, dest_res.y};

    outdated = 0;
}

Object::~Object(){
    if(texture)
        SDL_DestroyTexture(texture);
}
