#include "TextureManager.hpp"
#include <filesystem>

void Atlas::Assign_Sprite(Object* obj, int p_row, int p_column){
    obj->flags |= IMAGE;

    if(p_row >= rows || p_column >= columns){
        printf("Warning. No image at position %i, %i. File is %i, %i.\n", p_row, p_column, rows, columns);
        puts("Using default.");
        p_row = p_column = 0;
    }

    Vector2 top_left;
    Texture_Wrapper& image = obj->image;
    top_left.x = p_column*resolution.x;
    top_left.y = p_row*resolution.y;
    image.texture = texture;
    image.source = {top_left.x, top_left.y, resolution.x, resolution.y};
}

void Atlas::Assign_Sprite(Object* obj, int pos){
    int row = floor(pos/columns);
    int column = pos - row*columns;
    Assign_Sprite(obj, row, column);
}

Atlas::~Atlas(){
    SDL_DestroyTexture(texture);
}

TextureManager::TextureManager(SDL_Renderer* p_renderer, const Vector2& p_window_res):
    renderer(p_renderer), window_res(p_window_res){
    const char font_path[] = "Include/font.ttf";
    font = TTF_OpenFont(font_path, 52);
    if(!font){
        printf("Error. Failed to open font at %s\n", font_path);
        exit(1);
    }
}

Atlas* TextureManager::Load(const char* path, int rows, int columns){
    if(!std::filesystem::exists(path)){
        printf("Warning: Couldn't find texture at %s\n", path);
        return NULL;
    }

    if(!renderer){
        printf("renderer = %i\n", renderer);
        exit(1);
    }
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    if(!texture){
        puts(SDL_GetError());
        exit(1);
    }
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
    if(font)
        TTF_CloseFont(font);
    for(Atlas* atlas: textures){
        delete atlas;
    }
}
