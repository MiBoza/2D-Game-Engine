#include "Wheels.hpp"

int main(){
    Window_Data window_data("Wheels and Aliasing");
    window_data.Set_Font_Path("../../Include/font.ttf");
    window_data.Create_Window();
    Wheels* game;

    try{
        game = new Wheels(window_data);
        game->SetUp();

        while(game->state){
            game->input->Input_Update();
            game->Timing();
            game->Update();
            game->Components();
        }

        delete game;
    }
    catch(std::exception& e){
        puts(e.what());
        if(window_data.flags & SCENE_READY)
            delete game;
    }

    return 0;
}
