#include "Input_Handler.hpp"

constexpr float step = 100*360e-6; // 100 mHz

class Game : public Silly_Core{
    using Silly_Core::Silly_Core;

    Atlas* a_wheel, *m_atlas;
    Object* wheel, *textbox;
    Input_Handler* my_input;

    float frame_frequency;  // deg/milisecond
    std::string f_string;

    void Update_Display();
public:
    void SetUp();
    void Update();
};

void Game::Update_Display(){
    float frequency = frame_frequency/0.360;  // Hz
    f_string = "f = ";
    f_string += std::to_string(frequency).substr(0, 5);
    f_string += " Hz";
    Set_Text(textbox, f_string);
}

void Game::SetUp(){
    input = new Input_Handler(state);
    my_input = reinterpret_cast<Input_Handler*>(input);
    a_wheel = texture_manager->Load("Assets/Wheel.png", 1, 2);
    m_atlas = texture_manager->Load("Assets/Atlas.png", 2, 5);
    wheel = AddEXObject();
    wheel->Set_Size({550, 550});
    wheel->Set_Pos({295.7, 299.1});
    a_wheel->Assign_Sprite(wheel, 1);

    textbox = AddTextBox("f = 0 Hz");
    textbox->Set_Pos({703.1, 520.6});
    textbox->Set_Size({386.1, 164.32});
    m_atlas->Assign_Sprite(textbox, 8);

    frame_frequency = 0;

    Set_Framerate(45);
    // Timelimit_Thread(1000);
}

void Game::Update(){
    if(my_input->up_k & POSEDGE){
        frame_frequency += step;
        Update_Display();
    }
    if(my_input->down_k & POSEDGE){
        frame_frequency -= step;
        Update_Display();
    }
    wheel->rotation_angle += frame_frequency*delta_time;
}

int main(){
    Game* game = new Game("Wheels and Aliasing");
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
