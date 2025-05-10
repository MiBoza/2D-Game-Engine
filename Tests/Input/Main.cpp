#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    RigidBody* player;
    Atlas* circle;
    float p_speed = 0.03;
    Vector2 texture_res = {787, 787};

    RigidBody* Init_Rb(Atlas* atlas, const Vector2& size);
public:
    void SetUp();
    // void Update();
};

RigidBody* Game::Init_Rb(Atlas* atlas, const Vector2& size){
    RigidBody* rb;
    rb = AddRigidBody();

    Object* obj = rb->object;
    atlas->Assign_Sprite(obj);
    obj->Set_Size(size);

    return rb;
}

void Game::SetUp(){
    circle = texture_manager->Load("assets/Circle.png", texture_res);
    Vector2 size({20, 20});

    player = Init_Rb(circle, size);
    // player->velocity = {0.1, 0.01};
    // Set_Framerate(20);
}

// void Game::Update(){
// }

int main(){
    Game* game = new Game("Player Movement");
    game->SetUp();

    while(game->running){
        game->Input_Handler();
        game->Timing();
        // game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
