#include "TextureManager.hpp"

TextureManager::TextureManager(SDL_Renderer* p_renderer, const Vector2& p_window_res):
    renderer(p_renderer), window_res(p_window_res){}

int TextureManager::Load(const char* path, const Vector2& p_texture_res){
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    Vector2 resolution = p_texture_res;
    textures.push_back(texture);
    resolutions.push_back(resolution);

    return textures.size() - 1;
}

TextureManager::~TextureManager(){
    for(SDL_Texture* texture: textures){
        SDL_DestroyTexture(texture);
    }
}
