#include "Aggregate.hpp"
#include "Basics.h"

class Game : public Aggregate{
    using Aggregate::Aggregate;

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
    atlas = texture_manager->Load("Assets/Atlas.png", 2, 5);
    box = AddTextBox("1");
    atlas->Assign_Sprite(box, 1, 3);
    box->Set_Size({420, 250});
    // Set_Framerate(3);
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
    Game* game = new Game("Load Sprites");
    game->SetUp();

    while(game->running){
        game->input.Input_Update();
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
