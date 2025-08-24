#ifndef Aggregate_hpp
#define Aggregate_hpp

#include "TextureManager.hpp"
#include "RigidBody.hpp"
#include "Input_Handler.hpp"

class Event{
public:
    Behaviour* behaviour;
    int start, end;
};

class Aggregate{
public:
    Aggregate(const char* title, bool fullscreen = 0);
    ~Aggregate();
    void Components();
    void Event_Handler();
    void Timing();

    bool running = 0;
    Input_Handler input{running};
protected:
    Object* AddObject(RigidBody* p_rb = NULL);
    Object* AddEXObject(RigidBody* p_rb = NULL);
    Object* AddTextBox(const char line[] = " ");
    void Set_Text(Object* obj, const char line[]);
    RigidBody* AddRigidBody(Object* object = nullptr);
    void AddEvent(Event&& event);
    void Set_Framerate(float framerate);
    void Timelimit_Thread(int miliseconds);
    void Timelimit_Event(int miliseconds);

    Uint32 runtime = 1;
    Uint32 delta_time;
    Uint32 frame_number = 0;
    Vector2 window_res{900, 600};
    TextureManager* texture_manager;
private:
    void Destroy_Object(Object* obj);
    void Render(const Object* obj, const Texture_Wrapper& tx_wrap);

    float frame_delay = 40;
    Uint32 last_frame;
    int to_wait;
    list<Event> events;
    list<SDL_Thread*> threads;
    list<Object*> objects;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint32 relaxation = 0;
};

class Finish : public Behaviour{
    bool& running;
public:
    Finish(bool& p_running);
    void execute() override;
};

#endif //Aggregate_hpp
