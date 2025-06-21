#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    Atlas* a_arrow;
    // Atlas* a_square;
    // Vector2 texture_res = {787, 787};

    Object *arrow;
    // Object *square;

    Object* Init_Object(Atlas* atlas, const Vector2& size);
public:
    void SetUp();
    void Update();
};

Object* Game::Init_Object(Atlas* atlas, const Vector2& size){
    Object* obj;

    obj = AddObject();
    atlas->Assign_Sprite(obj);
    obj->Set_Size(size);

    return obj;
}

void Game::SetUp(){
    a_arrow = texture_manager->Load("Assets/Arrow.png");
    // a_square = texture_manager->Load("assets/Square.png", {787, 266});

    arrow = Init_Object(a_arrow, {120, 40});
    // square = Init_Object(a_square, {20, 20});

    // Set_Framerate(2);
}

void Game::Update(){
    // const static float frequency = 0.12;
    const static float frequency = -0.24;

    arrow->Rotate(frequency*runtime);
    // arrow->Flip_Horizontally();

    // circle1->Set_Pos( Swirl(frequency*runtime +   0) );
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
