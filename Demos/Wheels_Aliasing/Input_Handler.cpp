#include "Input_Handler.hpp"

void KeyDown(short& key){
	key <<= 1;
	key |= CURRENT;
	if(!(key & PREVIOUS))
		key |= POSEDGE;
}

void Input_Handler::Input_Update(){
	SDL_PollEvent(&event);
	// Prevent previous bit from setting posedge bit
	up_k   &= CURRENT;
	down_k &= CURRENT;

	if(event.type == SDL_QUIT)
		state = 0;
	if(event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym){
		case SDLK_UP:
			KeyDown(up_k);
			break;
		case SDLK_DOWN:
			KeyDown(down_k);
			break;
		}
	}
	if(event.type == SDL_KEYUP){
		switch(event.key.keysym.sym){
		case SDLK_UP:
			up_k = RESET;
			break;
		case SDLK_DOWN:
			down_k = RESET;
			break;
		}
	}
}
