#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Vector2.hpp"

class TextureManager{
public:
    TextureManager(SDL_Renderer* p_renderer, const Vector2& p_window_res);
    int Load(const char* path, const Vector2& p_texture_res);
    SDL_Texture* Assign(const char* path);
    ~TextureManager();
    friend class Object;
    friend class Game;
private:
    std::vector<SDL_Texture*> textures;
    std::vector<Vector2> resolutions;
    Vector2 window_res;
    SDL_Renderer* renderer;
};

#endif // TextureManager_hpp
