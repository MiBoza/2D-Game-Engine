#include "Others.hpp"

Input_Base::Input_Base(short& p_state):
    state(p_state){}

void Default_Input::Input_Update(){
	SDL_PollEvent(&event);

	if(event.type == SDL_QUIT)
		state = 0;
}

Finish::Finish(short& p_state):
    state(p_state){}

void Finish::execute(){
    state = 0;
}

Texture_Wrapper::Texture_Wrapper():
    texture(NULL){}
