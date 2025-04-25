#include "Aggregate.hpp"

int main(){
    Aggregate* game = new Aggregate("Window Title");

    while(game->running){
        game->Input_Handler();
        game->Components();
    }

    delete game;

    return 0;
}
