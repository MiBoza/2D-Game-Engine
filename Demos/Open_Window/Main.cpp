#include "Silly_Core.hpp"

int main(){
    Window_Data window_data("Window Title");
    window_data.Set_Font_Path("../../Include/font.ttf");
    window_data.Create_Window();
    Silly_Core* game = new Silly_Core(window_data);
    game->input = new Default_Input(window_data.state);

    while(window_data.state){
        game->input->Input_Update();
        game->Components();
    }

    delete game;

    return 0;
}
