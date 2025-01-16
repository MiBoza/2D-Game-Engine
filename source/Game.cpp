#include "Game.hpp"

Game::Game(const char* title, int width, int height, bool fullscreen){
    const int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
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

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        puts("Renderer diddn't initialise");
        exit(1);
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Red, Green. Blue, Something

    running = 1;
}
void Game::Event_Handler(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
        running = 0;
}
void Game::Render(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
Game::~Game(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    puts("Game ended");
}
