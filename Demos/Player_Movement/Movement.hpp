#ifndef Movement_hpp
#define Movement_hpp

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

class Movement : public Silly_Core{
    using Silly_Core::Silly_Core;

    RigidBody* player;
    Atlas* atlas;
    Input_Handler* my_input;

    RigidBody* Init_Rb(Atlas* atlas, const Vector2& size);
public:
    void SetUp();
    void Update();
};

#endif	//Movement_hpp
