#ifndef Timing_hpp
#define Timing_hpp

#include "Aggregate.hpp"

Object* Aggregate::AddTextBox(const char line[]){
    Object* object = AddObject();
    object->flags |= TEXT;
    Set_Text(object, line);

    return object;
}

void Aggregate::Set_Text(Object* obj, const char line[]){
    if(!(obj->flags & TEXT)){
        puts("Warning. Trying to set text to object without TEXT flag");
        return;
    }
    Texture_Wrapper& text = obj->text;
    if(text.texture)
        SDL_DestroyTexture(text.texture);

    obj->colour = {0x00, 0x00, 0x00, 0xFF};
    text.source.x = 0;
    text.source.y = 0;
    SDL_Surface* Surface = TTF_RenderText_Blended(texture_manager->font, line, obj->colour);
    text.texture = SDL_CreateTextureFromSurface(renderer, Surface);
    if(!text.texture){
        puts("Error. Text failed to render");
        puts( SDL_GetError() );
        exit(1);
    }
    obj->flags |= OUTDATED;
    SDL_QueryTexture(text.texture, NULL, NULL, &text.source.w, &text.source.h);
    SDL_FreeSurface(Surface);
}

RigidBody* Aggregate::AddRigidBody(Object* object){
    RigidBody* rb = new RigidBody(delta_time, object);
    if(!rb->object)
        rb->object = AddObject(rb);
    return rb;
}

void Aggregate::AddEvent(Event&& event){
    if(events.size() == 0){
        events.push_back(event);
        return;
    }

    typename list<Event>::iterator it = events.end();
    do{
        --it;
        if( it->start <= event.start){
            ++it;
            events.insert(it, event);
            return;
        }
    }while( it != events.begin() );
    events.insert(it, event);
}

void Aggregate::Set_Framerate(float framerate){
    frame_delay = 1000.0/framerate;
    runtime = SDL_GetTicks();
    last_frame = runtime - frame_delay;
    to_wait = 0;
}

void Aggregate::Event_Handler(){
    if(events.size() == 0)
        return;

    Uint32& now = runtime;
    typename list<Event>::iterator it = events.begin();
    while( it != events.end() ){
        if(it->start > now)
            break;
        it->behaviour->execute();
        if(it->end <= now){
            delete it->behaviour;
            it = events.erase(it);
        }
        ++it;
    }
}

struct County{
    int miliseconds;
    bool* running;
};

int Countdown(void* ptr){
    County* data = reinterpret_cast<County*>(ptr);
    SDL_Delay(data->miliseconds);
    *data->running = 0;
    delete data;
    return 0;
}

void Aggregate::Timelimit_Thread(int miliseconds){
    County* data = new County(miliseconds, &running);
    SDL_Thread* thread = SDL_CreateThread(Countdown, "Countdown", data);
    threads.push_back(thread);
}

void Aggregate::Timelimit_Event(int miliseconds){
    Finish* finish = new Finish(running);
    Event event({finish, miliseconds});
    AddEvent( std::move(event) );
}

void Aggregate::Render(const Object* obj, const Texture_Wrapper& tx_wrap){
    if(obj->flags & COPYEX)
        SDL_RenderCopyEx(renderer, tx_wrap.texture, &tx_wrap.source, &tx_wrap.destination,
            obj->rotation_angle, NULL, obj->flip);
    else{
        SDL_RenderCopy(renderer, tx_wrap.texture, &tx_wrap.source, &tx_wrap.destination);
    }
}

Finish::Finish(bool& p_running):
    running(p_running){}

void Finish::execute(){
    running = 0;
}

#endif //Timing_hpp
