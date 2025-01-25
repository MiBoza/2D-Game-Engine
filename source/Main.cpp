#include "Game.hpp"
// #include <stdio.h>

Vector2 size({60, 60});
Vector2 window_res = {900, 600};
RigidBody* circle = NULL;
RigidBody* square = NULL;
RigidBody* square2 = NULL;

void Game::SetUp(){
    Vector2 texture_res({787, 787});

    int circle_index = texture_manager->Load("assets/Circle.png", texture_res);
    int square_index = texture_manager->Load("assets/Square.png", texture_res);

    circle = AddRigidBody();
    circle->Set_Texture(circle_index);
    circle->Set_Pos({350, 400});
    circle->Set_Size(size);
    circle->velocity = {0.2, -0.3};

    square = AddRigidBody();
    square->Set_Texture(square_index);
    square->Set_Pos({50, 500});
    square->Set_Size(size*0.8);
    square->velocity = {0.2, -0.8};
    // square->acceleration = {0, 0.015};

    square2 = AddRigidBody();
    square2->Set_Texture(square_index);
    square2->Set_Pos({350, 400});
    square2->Set_Size(size*1.2);
    square2->velocity = {0.3,-0.2};

    // Set_Framerate(2);
}

void Get_Back_In_There(float& pos_comp, float& vel_comp, float edge){
    float frac = (pos_comp - edge)/vel_comp;
    pos_comp -= 2*frac*vel_comp;
    vel_comp *= -1;
}

void Collision(RigidBody* rb){
    static int left_edge = size.x/2;
    static int right_edge = window_res.x - size.x/2;
    static int top_edge = size.y/2;
    static int bottom_edge = window_res.y - size.y/2;
    Vector2 pos = rb->Get_Pos();
    Vector2& velocity = rb->velocity;
    bool collided = 0;
    // printf("square.pos = ");
    // Print_Vector2(pos);

    if(pos.x <= left_edge)
        Get_Back_In_There(pos.x, velocity.x, left_edge);

    if(pos.y <= top_edge)
        Get_Back_In_There(pos.y, velocity.y, top_edge);

    if(pos.x >= right_edge)
        Get_Back_In_There(pos.x, velocity.x, right_edge);

    if(pos.y >= bottom_edge)
        Get_Back_In_There(pos.y, velocity.y, bottom_edge);
}

void Game::Update(){
    int runtime = SDL_GetTicks();
    if(circle){
        Collision(circle);
        if(runtime > 2000){
            circle->Destroy();
            circle = NULL;
        }
    }

    if(square){
        Collision(square);
        if(runtime > 4000){
            square->Destroy();
            square = NULL;
        }
    }

    if(square2){
        Collision(square2);
        if(runtime > 6000){
            square2->Destroy();
            square2 = NULL;
        }
    }
    if(runtime > 8000)
        running = 0;
}

int main(){
    Game* game = new Game("Mystery Title", 900, 600, 0);
    game->SetUp();

    while(game->running){
        game->Event_Handler();
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
