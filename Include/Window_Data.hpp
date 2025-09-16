#ifndef Window_Data_hpp
#define Window_Data_hpp

#include "Vector2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Window_Data{
public:
    Vector2 window_res;
    char font_path[20];
    bool fullscreen;
private:
    char* title;
	Uint32 frame_number = 0;
	Uint32 relaxation;
	Uint32 runtime = 1;
    SDL_Window* window;
    SDL_Renderer* renderer;

	friend class Silly_Core;
	friend class TextureManager;
public:
	short state;

	Window_Data(char* p_title, int p_state = 1);
    void Create_Window();
	~Window_Data();
};

#endif // Window_Data_hpp
