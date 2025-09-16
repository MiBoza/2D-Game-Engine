#include "Blocks.hpp"

Square_Bh::Square_Bh(Object* obj, float p_speed, const Uint32& delta_t):
    object(obj), speed(p_speed), delta_time(delta_t){}

void Square_Bh::execute(){
    Vector2 pos = object->Get_Pos();
    if(pos.y > 650){
        object->Destroy();
        puts("Square Destroyed");
        return;
    }

    pos.y += speed*delta_time;
    object->Set_Pos(pos);
}

Object* Blocks::Init_Square(int x){
    Vector2 pos({x, 750-x});
    Object* square = AddObject();
    square->Set_Pos(pos);
    square->Set_Size({50, 50});
    atlas->Assign_Sprite(square, 1, 1);
    Square_Bh* square_bh = new Square_Bh(square, square_speed, delta_time);
    square->Set_Behaviour(square_bh);

    return square;
}

void Blocks::SetUp(){
    input = new Default_Input(state);
    atlas = texture_manager->Load("Assets/Atlas.png", 2, 5);
    int range = 500;
    float delta = range/num_squares;
    float left = 450 - (num_squares-1)*delta/2;
    for(int i = 0; i < num_squares; i++){
        Init_Square(left + i*delta);
    }
    Set_Framerate(30);
    Timelimit_Thread(7000);
}
