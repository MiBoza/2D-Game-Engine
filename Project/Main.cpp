#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    RigidBody* player;
    float p_speed = 0.15;
    Atlas* circle;
    Vector2 texture_res = {787, 787};

    RigidBody* Init_Rb(Atlas* atlas, const Vector2& size);
public:
    void SetUp();
    void Update();
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
    circle = texture_manager->Load("Assets/Circle.png", texture_res);
    Vector2 size({20, 20});

    player = Init_Rb(circle, size);
    // player->velocity = {0.1, 0.02};
    Set_Framerate(30);
}

void Game::Update(){
    //Player Movement
    Vector2 p_velocity({0, 0});
    if(input.up_k)
        p_velocity.y -= 1;
    if(input.down_k)
        p_velocity.y += 1;
    if(input.right_k)
        p_velocity.x += 1;
    if(input.left_k)
        p_velocity.x -= 1;

    p_velocity.Normalise();
    p_velocity *= p_speed;
    player->velocity = p_velocity;
}

int main(){
    Game* game = new Game("Player Movement");
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
