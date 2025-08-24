#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Object.hpp"

#define CAPACITY 0x10000

class Atlas{
public:
    SDL_Texture* texture;
    int rows, columns;
    Vector2 resolution;
    bool deleted = 0;

    void Assign_Sprite(Object* obj, int row, int column);
    void Assign_Sprite(Object* obj, int pos = 0);
    friend class TextureManager;
private:
    ~Atlas();   //User should assign delete instead
};

class TextureManager{
public:
    const int& total_sprites = sprites;

    Atlas* Load(const char* path, int rows = 1, int columns = 1);
    TextureManager(SDL_Renderer* p_renderer, const Vector2& p_window_res);
    ~TextureManager();
    TTF_Font* font;
private:
    int sprites = 0;
    list<Atlas*> textures;
    Vector2 window_res;
    SDL_Renderer* renderer;
};

#endif // TextureManager_hpp
