#include "Game.hpp"
// #include <stdio.h>

Vector2 size({20, 20});
Vector2 window_res = {900, 600};
RigidBody* circle = NULL;
// RigidBody* square = NULL;
// RigidBody* square2 = NULL;

void Game::SetUp(){
    Vector2 texture_res({787, 787});

    int circle_index = texture_manager->Load("assets/Circle.png", texture_res);
    // int square_index = texture_manager->Load("assets/Square.png", texture_res);

    circle = AddRigidBody();
    circle->Set_Texture(circle_index);
    // circle->Set_Pos({350, 500});
    circle->Set_Pos({840, 70});
    circle->Set_Size(size);
    circle->velocity = {-0.35, -0.275};
    // circle->acceleration = {0.01, 0.015};
    circle->acceleration = {-0.01, 0.0};
    //
    // square = AddRigidBody();
    // square->Set_Texture(square_index);
    // square->Set_Pos({50, 500});
    // square->Set_Size(size*0.8);
    // square->velocity = {0.2, -0.8};
    // square->acceleration = {0, 0.015};
    //
    // square2 = AddRigidBody();
    // square2->Set_Texture(square_index);
    // square2->Set_Pos({350, 400});
    // square2->Set_Size(size*1.2);
    // square2->velocity = {0.3,-0.2};

    Set_Framerate(30);
}

void Collision(RigidBody* rb){
    const static int left_edge = size.x/2;
    const static int right_edge = window_res.x - size.x/2;
    const static int top_edge = size.y/2;
    const static int bottom_edge = window_res.y - size.y/2;

    //hy = kx + l
    const static Line left = {0, 1, -left_edge};
    const static Line right = {0, 1, -right_edge};
    const static Line top = {1, 0, top_edge};
    const static Line bottom = {1, 0, bottom_edge};

    Vector2 pos = rb->Get_Pos();

    if(pos.x <= left_edge)
        rb->Collide(left);

    if(pos.x >= right_edge)
        rb->Collide(right);

    if(pos.y <= top_edge)
        rb->Collide(top);

    if(pos.y >= bottom_edge)
        rb->Collide(bottom);
}

void Game::Update(){
    // Print_Vector2("\nb. pos = ", circle->Get_Pos());
    // Print_Vector2("b. vel = ", circle->velocity);

    // static int count = 3;
    // if(count-- == 0)
    //     running = 0;

    Collision(circle);

    // Print_Vector2("a. pos = ", circle->Get_Pos());
    // Print_Vector2("a. vel = ", circle->velocity);


    // if(circle){
    //     Collision(circle);
    //     if(runtime > 7000){
    //         circle->Destroy();
    //         circle = NULL;
    //     }
    // }
    //
    // if(square){
    //     Collision(square);
    //     if(runtime > 4000){
    //         square->Destroy();
    //         square = NULL;
    //     }
    // }
    //
    // if(square2){
    //     Collision(square2);
    //     if(runtime > 6000){
    //         square2->Destroy();
    //         square2 = NULL;
    //     }
    // }
    // if(runtime > 1800)
    //     running = 0;
}

int main(){
    Game* game = new Game("Mystery Title", 900, 600, 0);
    game->SetUp();
    // game->delta_time = 25;

    while(game->running){
        game->Event_Handler();
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
