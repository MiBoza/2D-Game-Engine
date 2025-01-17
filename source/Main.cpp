#include "Game.hpp"
// #include <stdio.h>

void Game::SetUp(){
    circle = new Object(renderer);
    circle->Set_Texture("assets/Circle.png");
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
