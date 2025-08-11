#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

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
    a_arrow = texture_manager->Load("Assets/Arrow.png");

    arrow = Init_Object(a_arrow, {120, 40});
}

void Game::Update(){
    // const static float frequency =  0.19;
    const static float frequency = -0.24;

    arrow->rotation_angle = frequency*runtime;
    // arrow->Flip_Horizontally();
}

int main(){
    Game* game = new Game("Infinity Swirl");
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
