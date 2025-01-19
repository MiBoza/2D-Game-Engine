#include "Game.hpp"
// #include <stdio.h>

Vector2 velocity({0.3, -0.2});
Vector2 pos({300, 400});
Vector2 size({60, 60});
Vector2 hsize = size/2;
Vector2 window_res = {900, 600};

void Game::SetUp(){
    Vector2 texture_res = {787, 787};
    circle = new Object(renderer, window_res);
    circle->Set_Texture("assets/Circle.png", texture_res);
    circle->Set_Pos(pos);
    circle->Set_Size(size);

    Set_Framerate(50);
}

void Game::Update(){
    pos += velocity*delta_time;
    circle->Set_Pos(pos);

    int left_edge = hsize.x;
    int right_edge = window_res.x - hsize.x;
    int top_edge = hsize.y;
    int bottom_edge = window_res.y - hsize.y;

    if(pos.x <= left_edge)
        velocity.x *= -1;
    if(pos.y <= top_edge)
        velocity.y *= -1;
    if(pos.x >= right_edge)
        velocity.x *= -1;
    if(pos.y >= bottom_edge)
        velocity.y *= -1;
}

int main(){
    Game* game = new Game("Mystery Title", 900, 600, 0);
    game->SetUp();

    while(game->running){
        game->Event_Handler();
        game->Timing();
        game->Update();
        game->Render();
    }

    delete game;

    return 0;
}
