#ifndef Input_Handler_hpp
#define Input_Handler_hpp

#include <SDL2/SDL.h>
#include "Silly_Core.hpp"

enum signal{
	RESET    = 0x0,
	CURRENT  = 0x1,
	PREVIOUS = 0x2,
	POSEDGE  = 0x4,
};

class Input_Handler : public Input_Base{
public:
	short up_k   = RESET;
	short down_k = RESET;

	using Input_Base::Input_Base;
	void Input_Update() override;
};

#endif	//Input_Handler_hpp
