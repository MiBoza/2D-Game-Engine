#ifndef Aggregate_hpp
#define Aggregate_hpp

#include "TextureManager.hpp"
#include "RigidBody.hpp"
#include <string>

class Event{
public:
    Behaviour* behaviour;
    int start, end;
};

class Input_Base{
protected:
	SDL_Event event;
	short& state;
public:
	Input_Base(short& p_state);
	virtual void Input_Update() = 0;
    virtual ~Input_Base() = default;
};

class Default_Input : public Input_Base{
    using Input_Base::Input_Base;
    void Input_Update() override;
};

enum signal{
	RESET    = 0x0,
	CURRENT  = 0x1,
	PREVIOUS = 0x2,
	POSEDGE  = 0x4,
};

struct Window_Data{
    Vector2 window_res;
    char* title;
    bool fullscreen;
    short state;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Window_Data(char* p_title, int p_state, int width = 900, int height = 600, bool p_fullscreen = 0);
    ~Window_Data();
};

class Aggregate{
public:
    Aggregate(Window_Data& p_window_data);
    ~Aggregate();
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
    Window_Data& window_data;
    Uint32 relaxation = 0;
};

class Finish : public Behaviour{
    short& state;
public:
    Finish(short& p_state);
    void execute() override;
};

#endif //Aggregate_hpp
