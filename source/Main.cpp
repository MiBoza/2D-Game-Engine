#include "Game.hpp"
// #include <stdio.h>

Vector2 cvelocity({0.3, -0.2});
Vector2 svelocity({0.2, -0.3});
Vector2 cpos({300, 400});
Vector2 spos({450, 200});
Vector2 size({60, 60});
Vector2 hsize = size/2;
Vector2 window_res = {900, 600};

void Game::SetUp(){
    Vector2 texture_res = {787, 787};
    circle = new Object(renderer, window_res);
    circle->Set_Texture("assets/Circle.png", texture_res);
    circle->Set_Pos(cpos);
    circle->Set_Size(size);

    square = new Object(renderer, window_res);
    square->Set_Texture("assets/Square.png", texture_res);
    square->Set_Pos(spos);
    square->Set_Size(size);

    Set_Framerate(30);
}

void Collision(Vector2& pos, Vector2& velocity){
    static int left_edge = hsize.x;
    static int right_edge = window_res.x - hsize.x;
    static int top_edge = hsize.y;
    static int bottom_edge = window_res.y - hsize.y;

    if(pos.x <= left_edge){
        velocity.x *= -1;
        pos += velocity*(left_edge - pos.x + 1);
    }
    if(pos.y <= top_edge){
        velocity.y *= -1;
        pos += velocity*(top_edge - pos.y + 1);
    }
    if(pos.x >= right_edge){
        velocity.x *= -1;
        pos += velocity*(pos.x - right_edge + 1);
    }
    if(pos.y >= bottom_edge){
        velocity.y *= -1;
        pos += velocity*(pos.y - bottom_edge + 1);
    }
}

void Game::Update(){
    cpos += cvelocity*delta_time;
    spos += svelocity*delta_time;

    Collision(cpos, cvelocity);
    Collision(spos, svelocity);

    circle->Set_Pos(cpos);
    square->Set_Pos(spos);
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
