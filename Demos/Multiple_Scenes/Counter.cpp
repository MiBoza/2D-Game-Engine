#include "Basics.h"
#include "Counter.hpp"

void Counter::SetUp(){
    input = new Counter_Input(state);
    my_input = reinterpret_cast<Counter_Input*>(input);
    atlas = texture_manager->Load("../../Assets/Atlas.png", 2, 5);
    box = AddTextBox("1");
    atlas->Assign_Sprite(box, 1, 3);
    box->Set_Size({420, 250});

    Set_Framerate(25);
}

void Counter::Update(){
    if(runtime - last_change > 1000){
        count <<= 1;
        itoa(count, box_buffer);
        Set_Text(box, box_buffer);
        last_change = runtime;
    }
    if(my_input->right_k & CURRENT)
        state = SWIRL;
}

void Counter_Input::KeyDown(short& key){
	key <<= 1;
	key |= CURRENT;
	if(!(key & PREVIOUS))
		key |= POSEDGE;
}

void Counter_Input::Input_Update(){
    SDL_PollEvent(&event);
    // Prevent previous bit from setting posedge bit
    right_k &= CURRENT;

    if(event.type == SDL_QUIT)
        state = FINISH;
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_RIGHT)
            KeyDown(right_k);
    }
    if(event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_RIGHT)
            right_k = RESET;
    }
}
