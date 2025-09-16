#include "Window_Data.hpp"

Window_Data::Window_Data(char* p_title, int p_state):
    title(p_title), state(p_state),
    font_path("Include/font.ttf"){
    window_res = {900, 600};
    fullscreen = 0;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Red, Green, Blue, Alpha
}

void Window_Data::Create_Window(){
    if(window)
        SDL_DestroyWindow(window);
    if(renderer)
        SDL_DestroyRenderer(renderer);

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

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

Window_Data::~Window_Data(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

	if(relaxation > runtime)
		relaxation = runtime;

	printf("Game ended after %i ms.\n", runtime);
	printf("Relaxed for %i ms (%.2f", relaxation, 100.0*relaxation/runtime);
	puts("%).");
}
