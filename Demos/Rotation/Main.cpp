#include "Silly_Core.hpp"

class Game : public Silly_Core{
    using Silly_Core::Silly_Core;

    Atlas* a_arrow;
    Object *arrow;

    Object* Init_Object(Atlas* atlas, const Vector2& size);
public:
    void SetUp();
    void Update();
};

Object* Game::Init_Object(Atlas* atlas, const Vector2& size){
    Object* obj;

    // EXObject enables rotating and flipping
    obj = AddEXObject();
    atlas->Assign_Sprite(obj);
    obj->Set_Size(size);

    return obj;
}

void Game::SetUp(){
    input = new Default_Input(state);
    a_arrow = texture_manager->Load("Assets/Arrow.png");

    arrow = Init_Object(a_arrow, {120, 40});
}

void Game::Update(){
    const static float frequency = 0.24;

    arrow->rotation_angle = frequency*runtime;
}

int main(){
    Game* game = new Game("Infinity Swirl");
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
