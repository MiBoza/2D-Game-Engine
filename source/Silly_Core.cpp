#include "Silly_Core.hpp"
using std::list;

Silly_Core::Silly_Core(Window_Data& p_window_data):
    window_data(p_window_data), state(p_window_data.state),
    frame_number(p_window_data.frame_number),
    relaxation(p_window_data.relaxation),
    runtime(p_window_data.runtime),
    texture_manager(nullptr),
    window_res(p_window_data.window_res){

    texture_manager = new TextureManager(p_window_data);
    if(!window_data.window)
        puts("Warning. No window in window_data. Try Create_Window()");

    window_data.flags |= SCENE_READY;
}

Silly_Core::~Silly_Core(){
    if(texture_manager)
        delete texture_manager;
    for(Object* obj : objects){
        delete obj;
    }
    for(Event& event : events)
        delete event.behaviour;
    for(SDL_Thread* thread : threads)
        SDL_WaitThread(thread, nullptr);
    if(input)
        delete input;

    window_data.flags &= ~SCENE_READY;
}

void Silly_Core::Components(){
    //Looks through the list of objects and
    //Renders or calculates physics as required

    SDL_RenderClear(window_data.renderer);
    typename std::list<Object*>::iterator it = objects.begin();
    for(; it != objects.end();){
        Object* object = *it;

        if(object->flags & DELETED){
            delete object;
            it = objects.erase(it);
            continue;
        }
        ++it;
        if(object->flags & OUTDATED)
            object->Update_Dest();
        if(object->flags & IMAGE)
            Render(object, object->image);
        if(object->flags & TEXT)
            Render(object, object->text);
        if(object->flags & BEHAVIOUR)
            object->behaviour->execute();
        if(object->flags & RIGIDBODY){
            RigidBody* rb = object->rb;
            rb->Rigid_Update();
        }
    }
    SDL_RenderPresent(window_data.renderer);
}

void Silly_Core::Timing(){
    runtime = SDL_GetTicks();
    ++frame_number;

    delta_time = runtime - last_frame;
    to_wait += frame_delay - delta_time;
    relaxation += to_wait;
    if(to_wait > 0)
        SDL_Delay(to_wait);
    else
        to_wait = 0;

    last_frame = window_data.runtime;
}

Object* Silly_Core::AddObject(RigidBody* p_rb){
    Object* object = new Object(p_rb);
    object->pos = window_res/2;
    objects.push_back(object);
    return object;
}

Object* Silly_Core::AddEXObject(RigidBody* p_rb){
    Object* object = AddObject(p_rb);
    object->flags |= COPYEX;
    return object;
}

Object* Silly_Core::AddTextBox(const char line[]){
    Object* object = AddObject();
    object->flags |= TEXT;
    Set_Text(object, line);

    return object;
}
