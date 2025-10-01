#ifndef Wheels_hpp
#define Wheels_hpp

#include <SDL2/SDL.h>
#include "Silly_Core.hpp"

class Input_Handler : public Input_Base{
public:
	short up_k   = RESET;
	short down_k = RESET;

	using Input_Base::Input_Base;
	void Input_Update() override;
};

class Wheels : public Silly_Core{
    using Silly_Core::Silly_Core;

    Atlas* a_wheel, *m_atlas;
    Object* wheel, *textbox;
    Input_Handler* my_input;

    float frame_frequency;  // deg/milisecond
    std::string f_string;
	float step;

    void Update_Display();
public:
    void SetUp();
    void Update();
};

#endif	//Wheels_hpp
