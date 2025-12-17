#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "RigidBody.hpp"

class Silly_Core;

class Atlas{
public:
    SDL_Texture* texture;
    int rows, columns;
    Vector2 resolution;
    bool deleted = 0;

    void Assign_Sprite(Object* obj, int p_row, int p_column);
    void Assign_Sprite(Object* obj, int pos = 0);
    void Assign_Sprite(RigidBody* rb, int row, int column);
    void Assign_Sprite(RigidBody* rb, int pos = 0);
    friend class TextureManager;
private:
    ~Atlas();   //User should assign delete instead
};

class TextureManager{
public:
    const int& total_sprites = sprites;

    Atlas* Load(const char* path, int rows = 1, int columns = 1);
    TextureManager(const Window_Data& window_data);
    ~TextureManager();
    TTF_Font* font;
private:
    SDL_Renderer* renderer;
    int sprites = 0;
    list<Atlas*> textures;
    Vector2 window_res;
};

#endif // TextureManager_hpp
