#include "Window_Data.hpp"

void Window_Data::Set_Font_Path(char* p_font_path){
    strcpy(font_path, p_font_path);
}

Window_Data::Window_Data(char p_title[], int p_state):
    state(p_state), window_res({900, 600}),
    frame_number(1), flags(EMPTY), runtime(1){

    title = new char[30];
    font_path = new char[60];
    strcpy(title, p_title);
    strcpy(font_path, "Include/font.ttf");

    window = nullptr;
    renderer = nullptr;

    strcpy(title, p_title);
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
}

void Window_Data::Create_Window(){
    if(window)
        SDL_DestroyWindow(window);
    if(renderer)
        SDL_DestroyRenderer(renderer);

    int SDL_flags = 0;
    if(flags & FULLSCREEN){
        SDL_flags = SDL_WINDOW_FULLSCREEN;
        window_res.x = 1920;
        window_res.y = 1080;
    }

    int pos_x, pos_y;
    pos_x = pos_y = SDL_WINDOWPOS_CENTERED;
    window = SDL_CreateWindow(title, pos_x, pos_y, window_res.x, window_res.y, SDL_flags);
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
    delete[] title;
    delete[] font_path;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

	if(relaxation > runtime)
		relaxation = runtime;

	printf("Game ended after %i ms.\n", runtime);
	printf("Relaxed for %i ms (%.2f", relaxation, 100.0*relaxation/runtime);
	puts("%).");
}
