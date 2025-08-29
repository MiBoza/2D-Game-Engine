#ifndef Input_Handler_hpp
#define Input_Handler_hpp

#include <SDL2/SDL.h>

enum signal{
	RESET    = 0x0,
	CURRENT  = 0x1,
	PREVIOUS = 0x2,
	POSEDGE  = 0x4,
};

class Input_Handler{
	SDL_Event event;
	bool& running;

public:
	short up_k   = RESET;
	short down_k = RESET;
	Input_Handler(bool& p_running);
	void Input_Update();
};

#endif	//Input_Handler_hpp
