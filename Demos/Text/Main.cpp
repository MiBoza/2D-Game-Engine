#include "Silly_Core.hpp"
#include "Basics.h"

class Game : public Silly_Core{
    using Silly_Core::Silly_Core;

    Object* box;
    Atlas* atlas;
    char box_buffer[11];
    int count = 1;
    int last_change;
public:
    void SetUp();
    void Update();
};

void Game::SetUp(){
    input = new Default_Input(state);
    atlas = texture_manager->Load("../../Assets/Atlas.png", 2, 5);
    box = AddTextBox("1");
    atlas->Assign_Sprite(box, 1, 3);
    box->Set_Size({420, 250});
}

void Game::Update(){
    if(runtime - last_change > 1000){
        count <<= 1;
        itoa(count, box_buffer);
        Set_Text(box, box_buffer);
        last_change = runtime;
    }
}

int main(){
    Window_Data window_data("Text Box");
    window_data.Set_Font_Path("../../Include/font.ttf");
    window_data.Create_Window();

    Game* game = new Game(window_data);
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
