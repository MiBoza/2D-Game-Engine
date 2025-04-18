#ifndef Aggregate_hpp
#define Aggregate_hpp

#include "RigidBody.hpp"
using std::list;

void Print_Rect(const SDL_Rect& rect);

struct Event{
    int start, finish;
    void (*f)();
};

class Aggregate{
public:
    Aggregate(const char* title, bool fullscreen = 0);
    void Input_Handler();
    void Components();
    void Timing();
    ~Aggregate();
    bool running = 0;
protected:
    Object* AddObject(RigidBody* p_rb = NULL);
    RigidBody* AddRigidBody(Object* object = NULL);
    void AddEvent(int start, int finish, void (*f)() );
    void Set_Framerate(float framerate);
    void Event_Handler();
    Uint32 current_frame;
    Uint32 delta_time;
    Vector2 window_res = {900, 600};
    TextureManager* texture_manager;
private:
    void Render(Object* obj);
    float frame_delay = 40;
    Uint32 relaxation = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    list<Object*> objects;
    list<Event*> events;
    void Destroy_Object(Object* obj);
};

#endif //Aggregate_hpp
