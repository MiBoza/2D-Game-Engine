#include "Wheels.hpp"

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

void Wheels::Update_Display(){
    float frequency = frame_frequency/0.360;  // Hz
    f_string = "f = ";
    f_string += std::to_string(frequency).substr(0, 5);
    f_string += " Hz";
    Set_Text(textbox, f_string);
}

void Wheels::SetUp(){
    input = new Input_Handler(state);
    my_input = reinterpret_cast<Input_Handler*>(input);
    a_wheel = texture_manager->Load("../../Assets/Wheels.png", 1, 2);
    m_atlas = texture_manager->Load("../../Assets/Atlas.png", 2, 5);
    wheel = AddEXObject();
    wheel->Set_Size({550, 550});
    wheel->Set_Pos({295.7, 299.1});
    a_wheel->Assign_Sprite(wheel, 0);

    textbox = AddTextBox("f = 0 Hz");
    textbox->Set_Pos({703.1, 520.6});
    textbox->Set_Size({386.1, 164.32});
    m_atlas->Assign_Sprite(textbox, 8);

    frame_frequency = 0;
	step = 100*360e-6; // 100 mHz

    Set_Framerate(45);
    // Timelimit_Thread(1000);
}

void Wheels::Update(){
    if(my_input->up_k & POSEDGE){
        frame_frequency += step;
        Update_Display();
    }
    if(my_input->down_k & POSEDGE){
        frame_frequency -= step;
        Update_Display();
    }
    wheel->rotation_angle += frame_frequency*delta_time;
}
