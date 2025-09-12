#include "Aggregate.hpp"

int main(){
    Aggregate* game = new Aggregate("Window Title");
    game->input = new Default_Input(game->state);

    while(game->state){
        game->input->Input_Update();
        game->Components();
    }

    delete game;

    return 0;
}
