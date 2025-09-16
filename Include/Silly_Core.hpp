#ifndef Silly_Core_hpp
#define Silly_Core_hpp

#include "TextureManager.hpp"
#include "RigidBody.hpp"
#include <string>

class Silly_Core{
public:
    Silly_Core(Window_Data& p_window_data);
    ~Silly_Core();
    void Components();
    void Event_Handler();
    void Timing();

    Input_Base* input;
    short& state;
protected:
    Object* AddObject(RigidBody* p_rb = nullptr);
    Object* AddEXObject(RigidBody* p_rb = nullptr);
    Object* AddTextBox(const char line[] = " ");
    void Set_Text(Object* obj, const char line[]);
    void Set_Text(Object* obj, const std::string line);
    RigidBody* AddRigidBody(Object* object = nullptr);
    void AddEvent(Event&& event);
    void Set_Framerate(float framerate);
    void Timelimit_Thread(int miliseconds);
    void Timelimit_Event(int miliseconds);

    Uint32& runtime;
    Uint32 delta_time;
    Uint32& frame_number;
    Uint32& relaxation;
    Vector2& window_res;
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
    Window_Data& window_data;
};

#endif //Silly_Core_hpp
