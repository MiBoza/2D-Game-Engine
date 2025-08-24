#ifndef Input_Handler_hpp
#define Input_Handler_hpp

#include <SDL2/SDL.h>

struct Input_Handler{
	SDL_Event event;
	bool& running;

	bool up_k = 0;
	bool down_k = 0;
	bool right_k = 0;
	bool left_k = 0;

	Input_Handler(bool& p_running);
	void Input_Update();
};

#endif	//Input_Handler_hpp
