#include "Silly_Core.hpp"
#include "Blocks.hpp"

int main(){
    Window_Data window_data("Load Sprites");
    Blocks* game = new Blocks(window_data);
    game->SetUp();

    while(window_data.state){
        game->input->Input_Update();
        game->Timing();
        game->Components();
    }

    delete game;

    return 0;
}
