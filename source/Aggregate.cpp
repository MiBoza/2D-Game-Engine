#include "Aggregate.hpp"
#include <filesystem>
using std::list;

Aggregate::Aggregate(const char* title, bool fullscreen){
    int flags = 0;
    Vector2& window_res = Aggregate::window_res;

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

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Red, Green, Blue, Something
    running = 1;

    texture_manager = new TextureManager(renderer, window_res);
}

Aggregate::~Aggregate(){
    delete texture_manager;
    texture_manager = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for(Object* obj : objects){
        Destroy_Object(obj);
    }
    for(Event* e : events){
        delete e;
    }

    if(relaxation > runtime)
        relaxation = runtime;

    printf("Game ended after %i ms.\n", runtime);
    printf("Relaxed for %i ms (%.2f", relaxation, 100.0*relaxation/runtime);
    puts("%).");
    SDL_Quit();
}

void Aggregate::Components(){
    //Looks through the list of objects and
    //Renders or calculates physics as required

    SDL_RenderClear(renderer);
    typename std::list<Object*>::iterator it = objects.begin();
    for(; it != objects.end();){
        Object* object = *it;

        if(object->flags & DELETED){
            Destroy_Object(object);
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
        if(object->rb){
            RigidBody* rb = object->rb;
            rb->Rigid_Update();
        }
    }
    SDL_RenderPresent(renderer);
}
#define time_limit;
// #define frame_limit;

void Aggregate::Timing(){
    runtime = SDL_GetTicks();
    ++frame_number;
    #ifdef time_limit
    if(runtime > 4700){
        running = 0;
        puts("Dying");
    }
    #endif
    #ifdef frame_limit
    if(frame_number > 14){
        running = 0;
        puts("Dying");
    }
    #endif

    static Uint32 last_frame = runtime - frame_delay;
    static int to_wait = 0;

    delta_time = runtime - last_frame;
    to_wait += frame_delay - delta_time;
    relaxation += to_wait;
    if(to_wait > 0)
        SDL_Delay(to_wait);

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
