#include "Game.hpp"
// #include <stdio.h>

Vector2  cpos({350, 400});
Vector2  spos({350, 400});
Vector2 s2pos({350, 400});
Vector2  cvelocity({0.3, 0.2});
Vector2  svelocity({0.2, 0.3});
Vector2 s2velocity({0.3,-0.2});


Vector2 size({60, 60});
Vector2 hsize = size/2;
Vector2 window_res = {900, 600};
Object* circle = NULL;
Object* square = NULL;
Object* square2 = NULL;

void Game::SetUp(){
    Vector2 texture_res({787, 787});

    int circle_index = texture_manager->Load("assets/Circle.png", texture_res);
    int square_index = texture_manager->Load("assets/Square.png", texture_res);

    circle = AddObject();
    AddRigidBody(circle);
    circle->Set_Texture(circle_index);
    circle->Set_Pos(cpos);
    circle->Set_Size(size);
    circle->Set_Velocity(cvelocity);

    square = AddObject();
    AddRigidBody(square);
    square->Set_Texture(square_index);
    square->Set_Pos(spos);
    square->Set_Size(size);
    square->Set_Velocity(svelocity);

    square2 = AddObject();
    AddRigidBody(square2);
    square2->Set_Texture(square_index);
    square2->Set_Pos(s2pos);
    square2->Set_Size(size);
    square2->Set_Velocity(s2velocity);

    // Set_Framerate(2);
}

void Get_Back_In_There(float& pos_comp, float& vel_comp, float edge){
    float frac = (pos_comp - edge)/vel_comp;
    pos_comp -= 2*frac*vel_comp;
    vel_comp *= -1;
}

void Collision(Object* object){
    static int left_edge = hsize.x;
    static int right_edge = window_res.x - hsize.x;
    static int top_edge = hsize.y;
    static int bottom_edge = window_res.y - hsize.y;
    Vector2 pos = object->Get_Pos();
    Vector2 velocity = object->Get_Velocity();
    bool collided = 0;

    if(pos.x <= left_edge){
        Get_Back_In_There(pos.x, velocity.x, left_edge);
        collided = 1;
    }
    if(pos.y <= top_edge){
        Get_Back_In_There(pos.y, velocity.y, top_edge);
        collided = 1;
    }
    if(pos.x >= right_edge){
        Get_Back_In_There(pos.x, velocity.x, right_edge);
        collided = 1;
    }
    if(pos.y >= bottom_edge){
        Get_Back_In_There(pos.y, velocity.y, bottom_edge);
        collided = 1;
    }

    if(collided){
        object->Set_Pos(pos);
        object->Set_Velocity(velocity);
    }
}

void Game::Update(){
    Collision(circle);
    Collision(square);
    Collision(square2);
}

int main(){
    Game* game = new Game("Mystery Title", 900, 600, 0);
    game->SetUp();

    while(game->running){
        game->Event_Handler();
        game->Timing();
        game->RigidUpdate();
        game->Update();
        game->Render();
    }

    delete game;

    return 0;
}
