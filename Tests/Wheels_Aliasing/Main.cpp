#include "Aggregate.hpp"
#include "Input_Handler.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    Atlas* image;
    Object* wheel;

    float step;
    float frequency;
public:
    Input_Handler input{running};
    void SetUp();
    void Update();
};

void Game::SetUp(){
    image = texture_manager->Load("Assets/Wheel.png", 1, 2);
    wheel = AddEXObject();
    wheel->Set_Size({550, 550});
    image->Assign_Sprite(wheel, 0);

    step = 0.360*0.14159; // 0.14159 kHz
    frequency = 0;

    // Set_Framerate(15);
    // Timelimit_Thread(1000);
}

void Game::Update(){
    if(input.up_k & POSEDGE)
        frequency += step;
    if(input.down_k & POSEDGE)
        frequency -= step;
    wheel->rotation_angle += frequency*delta_time;
}

int main(){
    Game* game = new Game("Wheels and Aliasing");
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
