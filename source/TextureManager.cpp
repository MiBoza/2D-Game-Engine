#include "TextureManager.hpp"
#include <filesystem>

void Atlas::Assign_Sprite(Object* obj, int p_row, int p_column){
    obj->flags |= RENDER;

    if(p_row >= rows || p_column >= columns){
        printf("Warning. No image at position %i, %i. File is %i, %i.\n", p_row, p_column, rows, columns);
        puts("Using default.");
        p_row = p_column = 0;
        obj->flags &= ~RENDER;
    }

    Vector2 top_left;
    top_left.x = p_column*resolution.x;
    top_left.y = p_row*resolution.y;
    obj->texture = texture;
    obj->source = {top_left.x, top_left.y, resolution.x, resolution.y};
}

Atlas::~Atlas(){
    SDL_DestroyTexture(texture);
}

TextureManager::TextureManager(SDL_Renderer* p_renderer, const Vector2& p_window_res):
    renderer(p_renderer), window_res(p_window_res){}

Atlas* TextureManager::Load(const char* path, int rows, int columns){
    if(!std::filesystem::exists(path)){
        printf("Warning: Couldn't find texture at %s\n", path);
        return NULL;
    }

    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    Atlas* atlas = new Atlas;

    atlas->texture = texture;
    atlas->rows = rows;
    atlas->columns = columns;
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    atlas->resolution.x = width/columns;
    atlas->resolution.y = height/rows;

    textures.push_back(atlas);

    return atlas;
}

TextureManager::~TextureManager(){
    for(Atlas* atlas: textures){
        delete atlas;
    }
}
