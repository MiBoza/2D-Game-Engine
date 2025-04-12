#include "Game.hpp"
// #include <stdio.h>

RigidBody* circle;
// void ByeBye_Circle(){
//     circle->Destroy();
//     circle = NULL;
// }
// void End_Game(){
//     running = 0;
// }

void Game::SetUp(){
    Vector2 texture_res({787, 787});
    Vector2 size({20, 20});

    int circle_index = texture_manager->Load("assets/Circle.png", texture_res);
    int square_index = texture_manager->Load("assets/Square.png", texture_res);

    circle = AddRigidBody();
    circle->Set_Texture(circle_index);
    circle->Set_Pos({450, 300});
    circle->Set_Size(size);
    circle->velocity = {-0.65, -0.275};
    // circle->acceleration = {-0.001, 0.006};

    // AddEvent(10000, 2999, ByeBye_Circle);
    // AddEvent(11500, 1999, End_Game);

    // Object* square = AddObject();
    // square->Set_Texture(square_index);
    // square->Set_Pos({161, 550});
    // square->Set_Size(size);
    // square->velocity = {0.2, -0.8};

    // Object* square2 = AddObject();
    // square2->Set_Texture(square_index);
    // square2->Set_Pos({739, 550});
    // square2->Set_Size(size);
    //
    // Object* square3 = AddObject();
    // square3->Set_Texture(square_index);
    // square3->Set_Pos({450, 50});
    // square3->Set_Size(size);

    Set_Framerate(5);
}

void Collision(RigidBody* rb){
    Vector2 size = rb->Get_Size();
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
    puts("1. Squat");
    if(circle)
        Collision(circle);
    // if(square)
    //     Collision(square);
    // if(square2)
    //     Collision(square2);
}

int main(){
    Game* game = new Game("Mystery Title");
    game->SetUp();

    while(running){
        game->Input_Handler();
        game->Event_Handler();
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
