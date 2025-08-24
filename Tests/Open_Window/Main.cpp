#include "Aggregate.hpp"

int main(){
    Aggregate* game = new Aggregate("Window Title");
    
    while(game->running){
        game->input.Input_Update();
        game->Components();
    }

    delete game;

    return 0;
}
