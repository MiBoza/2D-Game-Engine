#ifndef Window_Data_hpp
#define Window_Data_hpp

#include "Others.hpp"
#include "Vector2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Window_Data{
private:
    char* title;
    char* font_path;
	Uint32 frame_number;
	Uint32 relaxation;
	Uint32 runtime;
    SDL_Window* window;
    SDL_Renderer* renderer;

	friend class Silly_Core;
	friend class TextureManager;
public:
    int flags;
	short state = 1;
    Vector2 window_res;

    void Set_Font_Path(char* p_font_path);
	Window_Data(char p_title[], int p_state = 1);
    void Create_Window();
	~Window_Data();
};

#endif // Window_Data_hpp
