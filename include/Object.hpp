#ifndef Object_hpp
#define Object_hpp

#include "TextureManager.hpp"

class Object{
public:
    int texture_index;

    Object(const TextureManager* p_texture_manager);
    void Set_Pos(const Vector2& p_pos);
    void Set_Size(const Vector2& p_size);
    void Set_Texture(const int index);
    void Update_Dest();
    ~Object();
    friend class Game;
private:
    const TextureManager* texture_manager;
    bool outdated;
    Vector2 size;
    Vector2 pos;
    SDL_Rect source;
    SDL_Rect destination;
};

#endif // Object_hpp
