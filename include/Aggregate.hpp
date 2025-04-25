#ifndef Aggregate_hpp
#define Aggregate_hpp

#include "TextureManager.hpp"
using std::list;

struct Event{
    int start, finish;
    void (*f)();
};

class Aggregate{
public:
    Aggregate(const char* title, bool fullscreen = 0);
    ~Aggregate();
    void Input_Handler();
    void Components();
    void Timing();

    bool running = 0;
protected:
    Object* AddObject(RigidBody* p_rb = NULL);
    RigidBody* AddRigidBody(Object* object = NULL);
    void AddEvent(int start, int finish, void (*f)() );
    void Set_Framerate(float framerate);
    void Event_Handler();

    Uint32 runtime = 1;
    Uint32 delta_time;
    Uint32 frame_number = 0;
    TextureManager* texture_manager;
    Vector2 window_res = {900, 600};
private:
    void Destroy_Object(Object* obj);
    void Render(Object* obj);

    float frame_delay = 40;
    list<Object*> objects;
    list<Event*> events;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint32 relaxation = 0;
};

#endif //Aggregate_hpp
