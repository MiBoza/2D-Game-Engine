#include "Game.hpp"
// #include <stdio.h>

void Game::SetUp(){
    Vector2 window_res = {900, 600};
    Vector2 texture_res = {787, 787};
    circle = new Object(renderer, window_res);
    circle->Set_Texture("assets/Circle.png", texture_res);
    circle->Set_Pos({300, 50});
    circle->Set_Scale(1.0/4);

    // circle->Update_Dest();
    // printf("source = ");
    // PrintRect(circle->source);
    // printf("destination = ");
    // PrintRect(circle->destination);
}

void Game::Update(){
    static Vector2 velocity = {4, -2};
    static Vector2 pos({300, 400});

    pos += velocity;
    circle->Set_Pos(pos);
    // Print_Vector2(pos);

    if(pos.x <= 98)
        velocity.x *= -1;
    if(pos.y <= 98)
        velocity.y *= -1;
    if(pos.x >= 802)
        velocity.x *= -1;
    if(pos.y >= 502)
        velocity.y *= -1;

    SDL_Delay(10);
}

int main(){
    Game* game = new Game("Mystery Title", 900, 600, 0);
    game->SetUp();

    while(game->running){
        game->Event_Handler();
        game->Update();
        game->Render();
    }

    delete game;

    return 0;
}
