#include "Game.hpp"

int main(){
    Game* game = new Game("Window Title");

    while(game->running){
        game->Input_Handler();
        game->Components();
    }

    delete game;

    return 0;
}
