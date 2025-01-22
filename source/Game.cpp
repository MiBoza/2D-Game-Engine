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

void Game::Event_Handler(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
        running = 0;
}

void Game::Render(){
    SDL_RenderClear(renderer);
    for(Object* pointy : objects){
        SDL_Texture* pointy_texture = texture_manager->textures[pointy->texture_index];
        if(pointy_texture){
            if(pointy->outdated)
                pointy->Update_Dest();
            // Print_Rect(pointy->destination);
            SDL_RenderCopy(renderer, pointy_texture, &pointy->source, &pointy->destination);
        }
    }
    SDL_RenderPresent(renderer);
}

Object* Game::AddObject(){
    Object* pointy = new Object(texture_manager);
    objects.push_back(pointy);
    return pointy;
}

void Game::Set_Framerate(float framerate){
    framedelay = 1000.0/framerate;
}

void Game::Timing(){
    Uint32 current_frame = SDL_GetTicks();
    static Uint32 last_frame = current_frame;
    static int to_wait = 0;

    delta_time = current_frame - last_frame;
    to_wait += framedelay - delta_time;
    if(to_wait > 0)
        SDL_Delay(to_wait);

    last_frame = current_frame;
}

Game::~Game(){
    delete texture_manager;
    texture_manager = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    puts("Game ended");
}
