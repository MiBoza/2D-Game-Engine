#include "Movement.hpp"

RigidBody* Movement::Init_Rb(Atlas* atlas, const Vector2& size){
    RigidBody* rb;
    rb = AddRigidBody();

    Object* obj = rb->object;
    atlas->Assign_Sprite(obj);
    obj->Set_Size(size);

    return rb;
}

void Movement::SetUp(){
    input = new Input_Handler(state);
    my_input = reinterpret_cast<Input_Handler*>(input);
    circle = texture_manager->Load("../../Assets/Circle.png");
    Vector2 size({20, 20});

    player = Init_Rb(circle, size);
    Set_Framerate(30);
}

void Movement::Update(){
    // Player Movement
    Vector2 v({0, 0});
    static const float turn_speed = 0.15;
    static const float p_speed = 0.5;
    static const float a = 1-turn_speed;
    static const float b = turn_speed*p_speed;

    if(my_input->up_k)
        v += { 0, -1};
    if(my_input->down_k)
        v += { 0,  1};
    if(my_input->right_k)
        v += { 1,  0};
    if(my_input->left_k)
        v += {-1,  0};

    if(Is_Zero(v))
        player->velocity = v;
    else{
        v.Normalise();
        player->velocity *= a;
        player->velocity += b*v;
    }
}

void Input_Handler::Input_Update(){
	SDL_PollEvent(&event);
	if(event.type == SDL_QUIT)
		state = 0;
	if(event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym){
			case SDLK_UP:
				up_k = 1;
				break;
			case SDLK_DOWN:
				down_k = 1;
				break;
			case SDLK_RIGHT:
				right_k = 1;
				break;
			case SDLK_LEFT:
				left_k = 1;
				break;
		}
	}
	if(event.type == SDL_KEYUP){
		switch(event.key.keysym.sym){
			case SDLK_UP:
				up_k = 0;
				break;
			case SDLK_DOWN:
				down_k = 0;
				break;
			case SDLK_RIGHT:
				right_k = 0;
				break;
			case SDLK_LEFT:
				left_k = 0;
				break;
		}
	}
}
