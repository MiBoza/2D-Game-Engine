#ifndef Game_Timing_hpp
#define Game_Timing_hpp

#include "Game.hpp"

// #define time_limit 1500
const Uint32 time_limit = 1500;

void Game::Timing(Uint32 time_limit){
    Uint32 current_frame = SDL_GetTicks();
    // #ifdef time_limit
    if(current_frame > time_limit){
        running = 0;
        puts("Dying");
    }
    // #endif

    static Uint32 last_frame = current_frame;
    static int to_wait = 0;

    delta_time = current_frame - last_frame;
    to_wait += frame_delay - delta_time;
    relaxation += to_wait;
    if(to_wait > 0)
        SDL_Delay(to_wait);

    last_frame = current_frame;
}

void Game::Set_Framerate(float framerate){
    frame_delay = 1000.0/framerate;
}

void Game::AddEvent(int start, int finish, void (*f)() ){
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

void Game::Event_Handler(){
    if(events.size() == 0)
        return;

    Uint32 now = SDL_GetTicks();
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

#endif //Game_Timing_hpp
