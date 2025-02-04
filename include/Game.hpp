#ifndef Game_hpp
#define Game_hpp

#include "RigidBody.hpp"
using std::list;

void Print_Rect(const SDL_Rect& rect);

struct Event{
    int start, finish;
    void (*f)();
};

class Game{
public:
    Game(const char* title, int width, int height, bool fullscreen);
    void Input_Handler();
    void Components();
    void SetUp();
    Object* AddObject();
    RigidBody* AddRigidBody();
    void AddEvent(int start, int finish, void (*f)() );
    void Update();
    ~Game();
    void Timing();
    void Set_Framerate(float framerate);
    void Event_Handler();
    Uint32 delta_time;
    bool running;
private:
    void Render(Object* obj);
    float frame_delay = 40;
    Uint32 relaxation = 0;
    Vector2 window_res;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TextureManager* texture_manager;
    list<Object*> objects;
    list<Event*> events;
    void Destroy_Object(Object* obj);
};

#endif //Game_hpp
