#ifndef Aggregate_hpp
#define Aggregate_hpp

#include "TextureManager.hpp"
#include "Input_Handler.hpp"
using std::list;

struct Event{
    int start, finish;
    void (*f)();
};

class Aggregate{
public:
    Aggregate(const char* title, bool fullscreen = 0);
    ~Aggregate();
    void Components();
    void Timing();

    bool running = 0;
    Input_Handler input{running};
protected:
    Object* AddObject(RigidBody* p_rb = NULL);
    RigidBody* AddRigidBody(Object* object = NULL);
    void AddEvent(int start, int finish, void (*f)() );
    void Set_Framerate(float framerate);
    void Event_Handler();

    Uint32 runtime = 1;
    Uint32 delta_time;
    Uint32 frame_number = 0;
    Vector2 window_res{900, 600};
    TextureManager* texture_manager;
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
