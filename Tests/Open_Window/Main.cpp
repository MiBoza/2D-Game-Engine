#include "Aggregate.hpp"
#include "Input_Handler.hpp"

int main(){
    Aggregate* game = new Aggregate("Window Title");
    Input_Handler input(game->running);

    while(game->running){
        input.Input_Update();
        game->Components();
    }

    delete game;

    return 0;
}
