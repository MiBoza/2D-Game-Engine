#include "Game.hpp"

int main(){
    Game* game = new Game("Mystery Title", 300, 200, 0);

    while(game->running){
        game->Event_Handler();
        game->Render();
    }

    delete game;

    return 0;
}
