#include "Object.hpp"

Object::Object(SDL_Renderer* p_renderer){
    renderer = p_renderer;
    texture = NULL;
}

void Object::Set_Texture(const char* path){
    int width = 1920;
    int height = 1080;

    int size = height;
    int xcorner = (width - size)/2;
    int ycorner = (height - size)/2;
    destination = {xcorner, ycorner, size, size};

    texture = IMG_LoadTexture(renderer, path);
}

Object::~Object(){
    if(texture)
        SDL_DestroyTexture(texture);
}
