#ifndef Input_Handler_hpp
#define Input_Handler_hpp

#include <SDL2/SDL.h>
#include "Silly_Core.hpp"

class Input_Handler : public Input_Base{
public:
	bool up_k = 0;
	bool down_k = 0;
	bool right_k = 0;
	bool left_k = 0;

	using Input_Base::Input_Base;
	void Input_Update() override;
};

#endif	//Input_Handler_hpp
