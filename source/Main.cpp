#include "Game.hpp"
// #include <stdio.h>

void Game::SetUp(){
    Vector2 window_res = {900, 600};
    circle = new Object(renderer, window_res);
    circle->Set_Texture("assets/Circle.png");
    circle->Set_Pos({30, 450});
    circle->Set_Scale(1.0/3);

    circle->Update_Rects();
    printf("source = ");
    PrintRect(circle->source);
    printf("destination = ");
    PrintRect(circle->destination);
}

int main(){
    Game* game = new Game("Mystery Title", 900, 600, 0);
    game->SetUp();

    while(game->running){
        game->Event_Handler();
        game->Render();
    }

    delete game;

    return 0;
}
