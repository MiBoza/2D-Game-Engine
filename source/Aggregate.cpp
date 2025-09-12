#include "Aggregate.hpp"
// #include <filesystem>
using std::list;

Window_Data::Window_Data(char* p_title, int p_state, int width, int height, bool p_fullscreen):
    title(p_title), window_res({width, height}),
    state(p_state), fullscreen(p_fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
        window_res.x = 1920;
        window_res.y = 1080;
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        puts("SDL video couldn't initialise.");
        puts( SDL_GetError() );
        exit(1);
    }
    if(!IMG_Init(IMG_INIT_PNG)){
        puts("SDL_Image couldn't initialise.");
        puts( SDL_GetError() );
        exit(1);
    }
    if(TTF_Init() == -1){
        puts("SDL_ttf couldn't initialise.");
        puts( SDL_GetError() );
        exit(1);
    }
    int pos_x, pos_y;
    pos_x = pos_y = SDL_WINDOWPOS_CENTERED;
    window = SDL_CreateWindow(title, pos_x, pos_y, window_res.x, window_res.y, flags);
    if(!window){
        puts("Window couldn't open correctly");
        puts( SDL_GetError() );
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        puts("Renderer didn't initialise");
        puts( SDL_GetError() );
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Red, Green, Blue, Alpha
}

Window_Data::~Window_Data(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

Aggregate::Aggregate(Window_Data& p_window_data):
    window_data(p_window_data), state(p_window_data.state){
    texture_manager = new TextureManager(window_data.renderer, window_res);
}

Aggregate::~Aggregate(){
    delete texture_manager;
    texture_manager = nullptr;
    for(Object* obj : objects){
        delete obj;
    }
    for(Event& event : events)
        delete event.behaviour;
    for(SDL_Thread* thread : threads)
        SDL_WaitThread(thread, nullptr);
    if(input)
        delete input;
    if(relaxation > runtime)
        relaxation = runtime;

    printf("Silly scene ended after %i ms.\n", runtime);
    printf("Relaxed for %i ms (%.2f", relaxation, 100.0*relaxation/runtime);
    puts("%).\n");
}

void Aggregate::Components(){
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

void Aggregate::Timing(){
    runtime = SDL_GetTicks();
    ++frame_number;

    delta_time = runtime - last_frame;
    to_wait += frame_delay - delta_time;
    relaxation += to_wait;
    if(to_wait > 0)
        SDL_Delay(to_wait);
    else
        to_wait = 0;

    last_frame = runtime;
}

Object* Aggregate::AddObject(RigidBody* p_rb){
    Object* object = new Object(p_rb);
    object->pos = window_res/2;
    objects.push_back(object);
    return object;
}

Object* Aggregate::AddEXObject(RigidBody* p_rb){
    Object* object = AddObject(p_rb);
    object->flags |= COPYEX;
    return object;
}
