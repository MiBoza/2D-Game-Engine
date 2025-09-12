#include "Swirl.hpp"

Object* Swirl::Init_Object(int pos){
    Object* obj;

    obj = AddObject();
    atlas->Assign_Sprite(obj, pos);
    obj->Set_Size(size);

    return obj;
}

void Swirl::SetUp(){
    input = new Swirl_Input(state);
    my_input = reinterpret_cast<Swirl_Input*>(input);
    atlas = texture_manager->Load("Assets/Atlas.png", 2, 5);

    circle  = Init_Object(5);
    square1 = Init_Object(6);
    square2 = Init_Object(6);
    square3 = Init_Object(6);
    square4 = Init_Object(6);
    square5 = Init_Object(6);

    Set_Framerate(28);
}

Vector2 Swirling(float degrees){
    float angle = degrees*M_PI/180;

    Vector2 pos;

    pos.x = 450-400*cos(angle);
    pos.y = 300-100*sin(2*angle);

    return pos;
}

void Swirl::Update(){
    const static float frequency = 0.12;

    square1->Set_Pos( Swirling(frequency*runtime +  0) );
    square2->Set_Pos( Swirling(frequency*runtime + 24) );
    square3->Set_Pos( Swirling(frequency*runtime + 48) );
    square4->Set_Pos( Swirling(frequency*runtime + 72) );
    square5->Set_Pos( Swirling(frequency*runtime + 96) );
    circle->Set_Pos( Swirling(frequency*runtime + 120) );     //Lead

    if(my_input->left_k & CURRENT)
        state = COUNTER;
}

void Swirl_Input::KeyDown(short& key){
	key <<= 1;
	key |= CURRENT;
	if(!(key & PREVIOUS))
		key |= POSEDGE;
}

void Swirl_Input::Input_Update(){
    SDL_PollEvent(&event);
    // Prevent previous bit from setting posedge bit
    left_k   &= CURRENT;

    if(event.type == SDL_QUIT)
        state = FINISH;
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_LEFT)
            KeyDown(left_k);
    }
    if(event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_LEFT)
            left_k = RESET;
    }
}
