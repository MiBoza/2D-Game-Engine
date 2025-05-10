#ifndef Input_Handler_hpp
#define Input_Handler_hpp

#if __has_include("Input_Definitions.hpp")
	#include "Input_Definitions.hpp"
#endif	//__has_include("Input_Definitions.hpp")
#include <SDL2/SDL.h>

// #define UP_KEY:
// #define DOWN_KEY:
// #define RIGHT_KEY:
// #define LEFT_KEY:

struct Input_Handler{
	SDL_Event event;
	bool& running;

	#ifdef UP_KEY
	bool up_k = 0;
	#endif
	#ifdef DOWN_KEY
	bool down_k = 0;
	#endif
	#ifdef RIGHT_KEY
	bool right_k = 0;
	#endif
	#ifdef LEFT_KEY
	bool left_k = 0;
	#endif

	Input_Handler(bool& p_running);
	void Input_Update();
};

#endif	//Input_Handler_hpp
