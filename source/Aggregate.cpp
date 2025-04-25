#include "Aggregate.hpp"
using std::list;

Aggregate::Aggregate(const char* title, bool fullscreen){
    int flags = 0;
    Vector2& window_res = Aggregate::window_res;

    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
        window_res.x = 1920;
        window_res.y = 1080;
    }

    if(SDL_INIT_EVERYTHING == 0){
        puts("SDL couldn't initialise");
        exit(1);
    }
    int pos_x, pos_y;
    pos_x = pos_y = SDL_WINDOWPOS_CENTERED;
    window = SDL_CreateWindow(title, pos_x, pos_y, window_res.x, window_res.y, flags);
    if(!window){
        puts("Window couldn't open correctly");
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        puts("Renderer didn't initialise");
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Red, Green, Blue, Something
    running = 1;

    texture_manager = new TextureManager(renderer, window_res);
}

void Aggregate::Input_Handler(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
        running = 0;
}

void Aggregate::Destroy_Object(Object* obj){
    if(obj->rb)
        delete obj->rb;
    delete obj;
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
        if(object->flags & RENDER)
            Render(object);
        if(object->rb){
            RigidBody* rb = object->rb;
            rb->Rigid_Update();
        }
    }
    SDL_RenderPresent(renderer);
}

void Aggregate::Render(Object* obj){
    if(obj->outdated)
        obj->Update_Dest();
    SDL_RenderCopy(renderer, obj->texture, &obj->source, &obj->destination);
}

Object* Aggregate::AddObject(RigidBody* p_rb){
    Object* object = new Object(p_rb);
    object->pos = window_res/2;
    objects.push_back(object);
    return object;
}

RigidBody* Aggregate::AddRigidBody(Object* object){
    RigidBody* rb = new RigidBody(delta_time, object);
    if(!rb->object)
        rb->object = AddObject(rb);
    return rb;
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

    printf("Aggregate ended after %i ms.\n", runtime);
    printf("Relaxed for %i ms (%i", relaxation, 100*relaxation/runtime);
    puts("%).");
    SDL_Quit();
}
