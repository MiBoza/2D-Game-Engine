#include "Game.hpp"

int main(){
    Game* game = new Game("Mystery Title", 900, 600, 0);

    while(game->running){
        game->Event_Handler();
        game->Render();
    }

    delete game;

    return 0;
}
