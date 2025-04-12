#ifndef Game_hpp
#define Game_hpp

#include "RigidBody.hpp"
using std::list;

void Print_Rect(const SDL_Rect& rect);
bool running;
Vector2 window_res = {900, 600};

struct Event{
    int start, finish;
    void (*f)();
};

class Game{
public:
    Game(const char* title, bool fullscreen = 0);
    void Input_Handler();
    void Components();
    void SetUp();
    Object* AddObject(RigidBody* p_rb = NULL);
    RigidBody* AddRigidBody(Object* object = NULL);
    void AddEvent(int start, int finish, void (*f)() );
    void Update();
    ~Game();
    void Timing(Uint32 time_limit = 0);
    void Set_Framerate(float framerate);
    void Event_Handler();
    Uint32 delta_time;
private:
    void Render(Object* obj);
    float frame_delay = 40;
    Uint32 relaxation = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TextureManager* texture_manager;
    list<Object*> objects;
    list<Event*> events;
    void Destroy_Object(Object* obj);
};

#endif //Game_hpp
