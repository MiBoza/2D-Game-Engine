#include "Input_Handler.hpp"

Input_Handler::Input_Handler(bool& p_running):
	running(p_running){}

void Input_Handler::Input_Update(){
	SDL_PollEvent(&event);
	if(event.type == SDL_QUIT)
		running = 0;
	if(event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym){
		#ifdef UP_KEY
			case SDLK_UP:
				up_k = 1;
				break;
		#endif
		#ifdef DOWN_KEY
			case SDLK_DOWN:
				down_k = 1;
				break;
		#endif
		#ifdef RIGHT_KEY
			case SDLK_RIGHT:
				right_k = 1;
				break;
		#endif
		#ifdef LEFT_KEY
			case SDLK_LEFT:
				left_k = 1;
				break;
		#endif
		}
	}
	if(event.type == SDL_KEYUP){
		switch(event.key.keysym.sym){
		#ifdef UP_KEY
			case SDLK_UP:
				up_k = 0;
				break;
		#endif
		#ifdef DOWN_KEY
			case SDLK_DOWN:
				down_k = 0;
				break;
		#endif
		#ifdef RIGHT_KEY
			case SDLK_RIGHT:
				right_k = 0;
				break;
		#endif
		#ifdef LEFT_KEY
			case SDLK_LEFT:
				left_k = 0;
				break;
		#endif
		}
	}
}
