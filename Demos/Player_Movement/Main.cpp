#include "Silly_Core.hpp"
#include "Movement.hpp"

int main(){
    Window_Data window_data("Player Movement");
    window_data.Set_Font_Path("../../Include/font.ttf");
    window_data.Create_Window();

    Movement* game = new Movement(window_data);
    game->SetUp();

    while(game->state){
        game->input->Input_Update();
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
