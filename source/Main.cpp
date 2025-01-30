#include "Game.hpp"
// #include <stdio.h>

Vector2 size({60, 60});
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
    circle->Set_Pos({650.40, 49.40});
    circle->Set_Size(size);
    circle->velocity = {0.2, -0.3};
    //
    // square = AddRigidBody();
    // square->Set_Texture(square_index);
    // square->Set_Pos({50, 500});
    // square->Set_Size(size*0.8);
    // square->velocity = {0.2, -0.8};
    // // square->acceleration = {0, 0.015};
    //
    // square2 = AddRigidBody();
    // square2->Set_Texture(square_index);
    // square2->Set_Pos({350, 400});
    // square2->Set_Size(size*1.2);
    // square2->velocity = {0.3,-0.2};

    Set_Framerate(10);
}

void Collision(RigidBody* rb){
    static int left_edge = size.x/2;
    static int right_edge = window_res.x - size.x/2;
    static int top_edge = size.y/2;
    static int bottom_edge = window_res.y - size.y/2;

    //hy = kx + l
    static Line left = {0, 1, -left_edge};
    static Line right = {0, 1, -right_edge};
    static Line top = {1, 0, top_edge};
    static Line bottom = {1, 0, bottom_edge};

    Vector2 pos = rb->Get_Pos();

    printf("\npos = ");
    Print_Vector2(pos);
    printf("vel = ");
    Print_Vector2(rb->velocity);

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
    static int count = 5;
    if(count-- == 0)
        running = 0;

    Collision(circle);

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

int main(int argc, char** argv){
    Game* game = new Game("Mystery Title", 900, 600, 0);
    game->SetUp();
    // if(argc > 1)
    //     game->delta_time = 500;

    while(game->running){
        game->Event_Handler();
        // if(argc == 1)
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
