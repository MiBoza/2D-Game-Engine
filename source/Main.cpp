#include "Game.hpp"
// #include <stdio.h>

Vector2 cvelocity({0.4, -0.1});
Vector2 svelocity({0.2, -0.3});
Vector2 s2velocity({0.1, 0.3});
Vector2 cpos({300, 400});
Vector2 spos({450, 200});
Vector2 s2pos({350, 50});
Vector2 size({60, 60});
Vector2 hsize = size/2;
Vector2 window_res = {900, 600};
Object* circle = NULL;
Object* square = NULL;
Object* square2 = NULL;

void Game::SetUp(){
    Vector2 texture_res = {787, 787};

    circle = AddObject();
    circle->Set_Texture("assets/Circle.png", texture_res);
    circle->Set_Pos(cpos);
    circle->Set_Size(size);

    square = AddObject();
    square->Set_Texture("assets/Square.png", texture_res);
    square->Set_Pos(spos);
    square->Set_Size(size*1.2);

    square2 = AddObject();
    square2->Set_Texture("assets/Square.png", texture_res);
    square2->Set_Pos(s2pos);
    square2->Set_Size(size*0.8);

    // Set_Framerate(15);
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
    s2pos += s2velocity*delta_time;

    Collision(cpos, cvelocity);
    Collision(spos, svelocity);
    Collision(s2pos, s2velocity);

    circle->Set_Pos(cpos);
    square->Set_Pos(spos);
    square2->Set_Pos(s2pos);
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
