#include "Game.hpp"
using std::list;

void Print_Rect(const SDL_Rect& rect){
    printf("[%i, %i, %i, %i]\n", rect.x, rect.y, rect.h, rect.w);
}

Game::Game(const char* title, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
        width = 1920;
        height = 1080;
    }

    running = 0;
    if(SDL_INIT_EVERYTHING == 0){
        puts("SDL couldn't initialise");
        exit(1);
    }
    int pos_x, pos_y;
    pos_x = pos_y = SDL_WINDOWPOS_CENTERED;
    window = SDL_CreateWindow(title, pos_x, pos_y, width, height, flags);
    if(!window){
        puts("Window couldn't open correctly");
        exit(1);
    }

    window_res = {width, height};
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        puts("Renderer didn't initialise");
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Red, Green, Blue, Something
    running = 1;

    texture_manager = new TextureManager(renderer, window_res);
}

void Game::Input_Handler(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
        running = 0;
}

void Game::Destroy_Object(Object* obj){
    if(obj->flags & RIGID){
        RigidBody* rb = static_cast<RigidBody*>(obj);
        delete rb;
    }
    else
        delete obj;
}

void Game::Components(){
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
        if(object->flags & RIGID){
            RigidBody* rb = static_cast<RigidBody*>(object);
            rb->Rigid_Update();
        }
    }
    SDL_RenderPresent(renderer);
}

void Game::Render(Object* obj){
    if(obj->flags & RENDER){
        SDL_Texture* obj_texture = texture_manager->textures[obj->texture_index];
        if(obj->outdated)
            obj->Update_Dest();
        SDL_RenderCopy(renderer, obj_texture, &obj->source, &obj->destination);
    }
}

Object* Game::AddObject(){
    Object* pointy = new Object(texture_manager);
    pointy->pos = window_res/2;
    objects.push_back(pointy);
    return pointy;
}

RigidBody* Game::AddRigidBody(){
    RigidBody* pointy = new RigidBody(delta_time, texture_manager);
    pointy->pos = window_res/2;
    objects.push_back(pointy);
    return pointy;
}

Game::~Game(){
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

    Uint32 run_time = SDL_GetTicks();
    printf("Game ended after %i ms.\n", run_time);
    printf("Relaxed for %i ms (%i", relaxation, 100*relaxation/run_time);
    puts("%).");
    SDL_Quit();
}
