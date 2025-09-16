#include "Silly_Core.hpp"

int main(){
    Silly_Core* game = new Silly_Core("Window Title");
    game->input = new Default_Input(game->state);

    while(game->state){
        game->input->Input_Update();
        game->Components();
    }

    delete game;

    return 0;
}
