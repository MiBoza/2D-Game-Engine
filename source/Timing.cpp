#ifndef Timing_hpp
#define Timing_hpp

#include "Aggregate.hpp"

// define time_limit = 35000;

void Aggregate::Timing(){
    current_frame = SDL_GetTicks();
    #ifdef time_limit
    if(current_frame > time_limit){
        running = 0;
        puts("Dying");
    }
    #endif

    static Uint32 last_frame = current_frame;
    static int to_wait = 0;

    delta_time = current_frame - last_frame;
    to_wait += frame_delay - delta_time;
    relaxation += to_wait;
    if(to_wait > 0)
        SDL_Delay(to_wait);

    last_frame = current_frame;
}

void Aggregate::Set_Framerate(float framerate){
    frame_delay = 1000.0/framerate;
}

void Aggregate::AddEvent(int start, int finish, void (*f)() ){
    Event* e = new Event(start, finish, f);
    if(events.size() == 0){
        events.push_back(e);
        return;
    }

    typename list<Event*>::iterator it = events.end();
    do{
        --it;
        if( (*it)->start <= e->start ){
            ++it;
            events.insert(it, e);
            return;
        }
    }while( it != events.begin() );
    events.insert(it, e);
}

void Aggregate::Event_Handler(){
    if(events.size() == 0)
        return;

    Uint32& now = current_frame;
    typename list<Event*>::iterator it = events.begin();
    while( it != events.end() ){
        if((*it)->start > now)
            break;
        (*it)->f();
        if((*it)->finish <= now){
            delete *it;
            it = events.erase(it);
        }
        ++it;
    }
}

#endif //Timing_hpp
