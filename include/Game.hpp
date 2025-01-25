#ifndef Game_hpp
#define Game_hpp

#include "Object.hpp"

void Print_Rect(const SDL_Rect& rect);

class Game{
public:
    Game(const char* title, int width, int height, bool fullscreen);
    void Event_Handler();
    void Components();
    void SetUp();
    Object* AddObject();
    RigidBody* AddRigidBody();
    void Timing();
    void Set_Framerate(float framerate);
    void Update();
    ~Game();
    Uint32 delta_time;
    bool running;
private:
    void Render(Object* pointy);
    float frame_delay = 40;
    Vector2 window_res;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TextureManager* texture_manager;
    std::list<Object*> objects;
};

#endif //Game_hpp
