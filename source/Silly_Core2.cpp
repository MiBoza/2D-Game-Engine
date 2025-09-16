#include "Silly_Core.hpp"

void Silly_Core::Set_Text(Object* obj, const char line[]){
    if(!texture_manager->font){
        puts("Error. Trying to set text after failed font loading");
        exit(1);
    }
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
    text.texture = SDL_CreateTextureFromSurface(window_data.renderer, Surface);
    if(!text.texture){
        puts("Error. Text failed to render");
        puts( SDL_GetError() );
        exit(1);
    }
    obj->flags |= OUTDATED;
    SDL_QueryTexture(text.texture, NULL, NULL, &text.source.w, &text.source.h);
    SDL_FreeSurface(Surface);
}

void Silly_Core::Set_Text(Object* obj, const std::string line){
    const char* c_string = line.c_str();
    Set_Text(obj, c_string);
}

RigidBody* Silly_Core::AddRigidBody(Object* object){
    RigidBody* rb = new RigidBody(delta_time);
    if(!object)
        object = AddObject(rb);
    rb->object = object;
    object->flags |= RIGIDBODY;
    return rb;
}

void Silly_Core::AddEvent(Event&& event){
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

void Silly_Core::Set_Framerate(float framerate){
    frame_delay = 1000.0/framerate;
    runtime = SDL_GetTicks();
    last_frame = runtime - frame_delay;
    to_wait = 0;
}

void Silly_Core::Event_Handler(){
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
    short* state;
};

int Countdown(void* ptr){
    County* data = reinterpret_cast<County*>(ptr);
    SDL_Delay(data->miliseconds);
    *data->state = 0;
    delete data;
    return 0;
}

void Silly_Core::Timelimit_Thread(int miliseconds){
    County* data = new County(miliseconds, &state);
    SDL_Thread* thread = SDL_CreateThread(Countdown, "Countdown", data);
    threads.push_back(thread);
}

void Silly_Core::Timelimit_Event(int miliseconds){
    Finish* finish = new Finish(state);
    Event event({finish, miliseconds});
    AddEvent( std::move(event) );
}

void Silly_Core::Render(const Object* obj, const Texture_Wrapper& tx_wrap){
    if(obj->flags & COPYEX)
        SDL_RenderCopyEx(window_data.renderer, tx_wrap.texture, &tx_wrap.source, &tx_wrap.destination,
            obj->rotation_angle, NULL, obj->flip);
    else{
        SDL_RenderCopy(window_data.renderer, tx_wrap.texture, &tx_wrap.source, &tx_wrap.destination);
    }
}
